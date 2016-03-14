#include "MovieRecommender.h"
#include "Saver.h"

using namespace std;

MovieRecommender::MovieRecommender(int nbMovies, int nbUsers, int nbFeatures) {
  this->m_theta = gsl_matrix_alloc(nbUsers, nbFeatures);
  this->m_X = gsl_matrix_alloc(nbMovies, nbFeatures);
  this->m_parser = new DataParser(nbMovies, nbUsers);
  this->m_nbMovies = nbMovies;
  this->m_nbUsers = nbUsers;
  initParams();
  m_parser->parse();
}

MovieRecommender::MovieRecommender(string dataset, int nbMovies, int nbUsers, int nbFeatures) {
  this->m_theta = gsl_matrix_alloc(nbUsers, nbFeatures);
  this->m_X = gsl_matrix_alloc(nbMovies, nbFeatures);
  this->m_parser = new DataParser(dataset, nbMovies, nbUsers);
  this->m_nbMovies = nbMovies;
  this->m_nbUsers = nbUsers;
  initParams();
  m_parser->parse();
}

MovieRecommender::MovieRecommender(string dataset, int nbMovies, int nbUsers, gsl_matrix* theta, gsl_matrix* X) {
  this->m_theta = gsl_matrix_alloc(theta->size1, theta->size2);
  gsl_matrix_memcpy (this->m_theta, theta);
  this->m_X = gsl_matrix_alloc(X->size1, X->size2);
  gsl_matrix_memcpy (this->m_X, X);
  this->m_parser = new DataParser(dataset, nbMovies, nbUsers);
  this->m_nbMovies = nbMovies;
  this->m_nbUsers = nbUsers;
  m_parser->parse();
}

MovieRecommender::MovieRecommender(string dataset, Saver saver) {
  saver.load();
  this->m_theta = gsl_matrix_alloc(saver.getTheta()->size1, saver.getTheta()->size2);
  gsl_matrix_memcpy (this->m_theta, saver.getTheta());
  this->m_X = gsl_matrix_alloc(saver.getX()->size1, saver.getX()->size2);
  gsl_matrix_memcpy (this->m_X, saver.getX());
  this->m_parser = new DataParser(dataset, saver.getNbMovies(), saver.getNbUsers());
  this->m_nbMovies = saver.getNbMovies();
  this->m_nbUsers = saver.getNbUsers();
  m_parser->parse();
}

void MovieRecommender::train(double alpha, double lambda, int save) {
  double threshold = 3;
  double cost, oldcost;
  int i, j;
  gsl_matrix *error;
  gsl_matrix *regularizationX, *regularizationtheta;
  gsl_matrix *intermediateX, *intermediatetheta;

  i = save;
  j = 0;

  cost = 5.0;
  oldcost = cost;

  regularizationX = gsl_matrix_alloc(this->m_X->size1, this->m_X->size2);
  intermediateX = gsl_matrix_alloc(this->m_X->size1, this->m_X->size2);

  regularizationtheta = gsl_matrix_alloc(this->m_theta->size1, this->m_theta->size2);
  intermediatetheta = gsl_matrix_alloc(this->m_theta->size1, this->m_theta->size2);

  while(j < 500) {
    if(cost > oldcost) {
      // on diminue alpha
      cout << "minus alpha" << endl;
      alpha /= 5.0;
      cout << alpha << endl;
    }
    else {
      cout << "alpha x 2" << endl;
      //on augmente alpha
      alpha *= 2;
      cout << alpha << endl;
    }

    oldcost = cost;

    error = computeError();


    // on calcule la nouvelle matrice X(on effectue la decente de gradient)
    gsl_matrix_memcpy(regularizationX, this->m_X);
    gsl_matrix_scale(regularizationX, lambda);
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, error, m_theta, 0.0, intermediateX);
    gsl_matrix_add(intermediateX, regularizationX);
    gsl_matrix_scale(intermediateX, alpha);
    gsl_matrix_sub(m_X, intermediateX);

    // on calcule la nouvelle matrice theta(on effectue la decente de gradient)
    gsl_matrix_memcpy(regularizationtheta, this->m_theta);
    gsl_matrix_scale(regularizationtheta, lambda);
    gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1.0, error, m_X, 0.0, intermediatetheta);
    gsl_matrix_add(intermediatetheta, regularizationtheta);
    gsl_matrix_scale(intermediatetheta, alpha);
    gsl_matrix_sub(m_theta, intermediatetheta);

    cost = computeCost(lambda);
    printState(lambda);

    if(i == 0) {
      //cout << "saving ..." << endl;
      //saveState("train_result");
      i = save;
    }
    else {
      i--;
    }
    gsl_matrix_free(error);
    j++;
  }

  cout << "end gradient decent saving ..." << endl;

  saveState("train_result");

  gsl_matrix_free(regularizationX);
  gsl_matrix_free(regularizationtheta);
  gsl_matrix_free(intermediateX);
  gsl_matrix_free(intermediatetheta);
}

gsl_matrix* MovieRecommender::predict() {
  gsl_matrix *rates;
  gsl_matrix *ratings;

  ratings = gsl_matrix_alloc(m_nbMovies, m_nbUsers);
  rates = gsl_matrix_alloc(m_nbUsers, m_nbMovies);

  //(m_theta)*(m_X_t)
  gsl_blas_dgemm(CblasNoTrans,CblasTrans,
    1.0, m_X, m_theta,
    0.0, ratings);

    return ratings;
  }

  vector<string> MovieRecommender::recommend(int user, int nbMovies) {
    gsl_vector *user_rates, *movie, *other_movie, *res;
    int sum;
    unsigned int j, i, best_movie;
    vector<string> movies;

    user_rates = gsl_vector_alloc(this->m_parser->getDatas()->size2);
    other_movie = gsl_vector_alloc(this->m_parser->getDatas()->size1);
    movie = gsl_vector_alloc(this->m_parser->getDatas()->size1);
    res = gsl_vector_alloc(this->m_parser->getDatas()->size1);
    gsl_matrix_get_row(user_rates, this->m_parser->getDatas(), user);

    best_movie = gsl_vector_max_index(user_rates);

    gsl_matrix_get_row(movie, this->m_X, best_movie);

    for(i = 0; i < this->m_X->size2; ++i) {
      sum = 0;
      if(i != best_movie) {
        gsl_vector_memcpy(res, movie);
        gsl_matrix_get_row(other_movie, this->m_X, i);
        gsl_vector_sub(res, other_movie);
        for(j = 0; j < res->size; ++j) {
          sum += gsl_vector_get(res, j);
        }
        if(sum > -1 && sum < 1 ) {
          movies.push_back(this->m_parser->getMovies()[i]);
        }
      }
    }
    gsl_vector_free(user_rates);
    gsl_vector_free(movie);
    gsl_vector_free(other_movie);
    gsl_vector_free(res);

    return movies;
  }

  double MovieRecommender::computeCost(double lambda) {
    unsigned int i, j;
    double sumX, sumTheta, sumError;

    sumX = 0;
    sumTheta = 0;

    /*
    * Premier Element *
    * m_error_2 *
    */
    //calcul de m_error_t (transposée de m_error)
    gsl_matrix* error = computeError();
    //multiplication m_error*m_error_t dans m_error_2
    gsl_matrix* error_2 = gsl_matrix_alloc(error->size2, error->size2);
    gsl_blas_dgemm(CblasTrans,CblasNoTrans,
      1.0, error,error,
      0.0, error_2);

      /*
      * Deuxieme Element *
      */
      gsl_matrix *X_2 = gsl_matrix_alloc(m_X->size2, m_X->size2);
      gsl_blas_dgemm(CblasTrans,CblasNoTrans,
        1.0, m_X, m_X,
        0.0, X_2);

        sumX = 0;
        for(i = 0; i < X_2->size1; ++i) {
          for(j = 0; j < X_2->size2; ++j) {
            sumX += gsl_matrix_get(X_2, i, j);
          }
        }

        /*
        * Troisième élément
        */
        gsl_matrix * theta_2 = gsl_matrix_alloc(m_theta->size2, m_theta->size2);
        gsl_blas_dgemm(CblasTrans,CblasNoTrans,
          1.0, m_theta, m_theta,
          0.0, theta_2);



          sumTheta = 0;
          /* sommes des éléments */
          for(i = 0; i < theta_2->size1; ++i) {
            for(j = 0; j < theta_2->size2; ++j) {
              sumTheta += gsl_matrix_get(theta_2, i, j);
            }
          }

          sumError = 0;
          for(i = 0; i < error_2->size1; ++i) {
            for(j = 0; j < error_2->size2; ++j) {
              sumError += gsl_matrix_get(error_2, i, j);
            }
          }
          gsl_matrix_free(error);
          gsl_matrix_free(error_2);
          gsl_matrix_free(X_2);
          gsl_matrix_free(theta_2);

          return sqrt(1.0/15 * sumError + (lambda/2.0) * sumX + (lambda/2.0) * sumTheta);
        }

        gsl_matrix* MovieRecommender::computeError() {

          //computeError() = N*-N
          gsl_matrix* ratings;

          ratings = NULL;

          ratings = predict();
          //la différence ne pouvant pas jouer sur les valeurs non prédites
          //on remet a 0 celles non notés dans la copie de N*
          for (unsigned int i = 0; i < this->m_parser->getDatas()->size1; i++){
            for (unsigned int j = 0; j < this->m_parser->getDatas()->size2; j++){
              if (gsl_matrix_get(this->m_parser->getDatas(), i, j) == 0)
              gsl_matrix_set(ratings,i,j,0);
            }
          }
          gsl_matrix_sub(ratings, this->m_parser->getDatas());

          return ratings;
        }

        void MovieRecommender::saveState(string filename) {
          Saver saver = Saver(filename);
          saver.save(*this);
        }

        void MovieRecommender::loadState(string filename) {
          Saver saver = Saver(filename);
          saver.load();
        }

        void MovieRecommender::printState(double lambda) {
          //printMatrix("Theta", m_theta);
          //printMatrix("X", m_X);

          cout << "cout : " << computeCost(lambda) << endl;
        }

        void MovieRecommender::setDatas(string set, int nbMovies, int nbUsers) {
          this->m_parser = new DataParser(set, nbMovies, nbUsers);
          m_parser->parse();
        }

        gsl_matrix* MovieRecommender::getTheta() {
          return this->m_theta;
        }

        gsl_matrix* MovieRecommender::getX() {
          return this->m_X;
        }

        void MovieRecommender::initParams() {
          unsigned int i, j;
          const gsl_rng_type * T;
          gsl_rng * r;

          gsl_rng_env_setup();

          T = gsl_rng_default;
          r = gsl_rng_alloc(T);

          for(i = 0; i < m_theta->size1; ++i) {
            for(j = 0; j < m_theta->size2; ++j) {
              double n = gsl_rng_uniform(r);
              gsl_matrix_set(m_theta, i, j, n);
            }
          }

          for(i = 0; i < m_X->size1; ++i) {
            for(j = 0; j < m_X->size2; ++j) {
              double n = gsl_rng_uniform(r);
              gsl_matrix_set(m_X, i, j, n);
            }
          }
        }

        void MovieRecommender::printMatrix(string message, gsl_matrix *matrix) {
          cout << message << endl;
          for (unsigned int i = 0; i < matrix->size1; i++){
            for (unsigned int j = 0; j < matrix->size2; j++){
              cout << "|" << gsl_matrix_get(matrix, i ,j);
            }
            cout << "|" << endl;
          }
        }

        MovieRecommender::~MovieRecommender() {
          gsl_matrix_free(m_theta);
          gsl_matrix_free(m_X);
          delete(m_parser);
        }
