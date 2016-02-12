#include "MovieRecommender.h"
#include "Saver.h"

using namespace std;

MovieRecommender::MovieRecommender(int nbMovies, int nbUsers) {
  this->m_theta = NULL;
  this->m_X = NULL;
  this->m_ratings = gsl_matrix_alloc(nbMovies, nbUsers);
  this->m_parser = new DataParser(nbMovies, nbUsers);
  m_parser->parse();
}

MovieRecommender::MovieRecommender(string dataset, int nbMovies, int nbUsers) {
  this->m_theta = NULL;
  this->m_X = NULL;
  this->m_ratings = gsl_matrix_alloc(nbMovies, nbUsers);
  this->m_parser = new DataParser(dataset, nbMovies, nbUsers);
  m_parser->parse();
}

MovieRecommender::MovieRecommender(string dataset, int nbMovies, int nbUsers, gsl_matrix* theta, gsl_matrix* X) {
  this->m_theta = gsl_matrix_alloc(theta->size1, theta->size2);
  gsl_matrix_memcpy (this->m_theta, theta);
  this->m_X = gsl_matrix_alloc(X->size1, X->size2);
  gsl_matrix_memcpy (this->m_X, X);
  this->m_ratings = gsl_matrix_alloc(nbMovies, nbUsers);
  this->m_parser = new DataParser(dataset, nbMovies, nbUsers);
  //m_parser.parse();
}

MovieRecommender::MovieRecommender(string dataset, Saver saver) {
  saver.load();
  this->m_theta = saver.getTheta();
  this->m_X = saver.getX();
  this->m_ratings = gsl_matrix_alloc(saver.getNbMovies(), saver.getNbUsers());
  this->m_parser = new DataParser(dataset, saver.getNbMovies(), saver.getNbUsers());
  m_parser->parse();
}

void MovieRecommender::train(double alpha, double lambda) {
  double threshold = 0.1;
  gsl_matrix *error;
  gsl_matrix *regularizationX, *regularizationtheta;
  gsl_matrix *intermediateX, *intermediatetheta;

  regularizationX = gsl_matrix_alloc(this->m_X->size1, this->m_X->size2);
  intermediateX = gsl_matrix_alloc(this->m_X->size1, this->m_X->size2);

  regularizationtheta = gsl_matrix_alloc(this->m_theta->size1, this->m_theta->size2);
  intermediatetheta = gsl_matrix_alloc(this->m_theta->size1, this->m_theta->size2);

  while(computeCost(alpha) > threshold) {
    error = computeError();

    // on calcule la nouvelle matrice X(on effectue la decente de gradient)
    gsl_matrix_memcpy(regularizationX, this->m_X);
    gsl_matrix_scale(regularizationX, lambda);
    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, error, m_theta, 0.0, intermediateX);
    gsl_matrix_add(intermediateX, regularizationX);
    gsl_matrix_scale(intermediateX, alpha);
    gsl_matrix_sub(m_X, intermediateX);

    // on calcule la nouvelle matrice theta(on effectue la decente de gradient)
    gsl_matrix_memcpy(regularizationtheta, this->m_theta);
    gsl_matrix_scale(regularizationtheta, lambda);
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, error, m_X, 0.0, intermediatetheta);
    gsl_matrix_add(intermediatetheta, regularizationtheta);
    gsl_matrix_scale(intermediatetheta, alpha);
    gsl_matrix_sub(m_theta, intermediatetheta);
  }

  saveState("train_result");

  gsl_matrix_free(error);
  gsl_matrix_free(regularizationX);
  gsl_matrix_free(regularizationtheta);
  gsl_matrix_free(intermediateX);
  gsl_matrix_free(intermediatetheta);
}

void MovieRecommender::predict() {
  gsl_matrix *rates;

  rates = gsl_matrix_alloc(m_ratings->size2, m_ratings->size1);

  //(m_theta)*(m_X_t)
  gsl_blas_dgemm(CblasNoTrans,CblasTrans,
    1.0, m_theta,m_X,
    0.0, rates);

    gsl_matrix_transpose_memcpy(m_ratings, rates);
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
    gsl_vector *v, *row;
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
    gsl_matrix* error_2 = gsl_matrix_alloc(error->size1, error->size2);
    gsl_blas_dgemm(CblasNoTrans,CblasTrans,
      1.0, error,error,
      0.0, error_2);
      /*
      * Deuxieme Element *
      */
      gsl_matrix *X_2 = gsl_matrix_alloc(m_X->size1, m_X->size2);
      gsl_blas_dgemm(CblasTrans,CblasNoTrans,
        1.0, m_X, m_X,
        0.0, X_2);

        v = gsl_vector_calloc(X_2->size2);
        row = gsl_vector_calloc(X_2->size2);

        /* sommes des éléments */
        for(i = 0; i < X_2->size1; ++i) {
          gsl_matrix_get_row(row, X_2, i);
          gsl_vector_add(v, row);
        }

        for(i = 0; i < X_2->size2; ++i) {
          sumX += gsl_vector_get(v, i);
        }

        /*
        * Troisième élément
        */
        gsl_matrix * theta_2 = gsl_matrix_alloc(m_theta->size1, m_theta->size2);
        gsl_blas_dgemm(CblasTrans,CblasNoTrans,
          1.0, m_theta, m_theta,
          0.0, theta_2);

          v = gsl_vector_calloc(theta_2->size2);
          row = gsl_vector_calloc(theta_2->size2);

          /* sommes des éléments */
          for(i = 0; i < theta_2->size1; ++i) {
            gsl_matrix_get_row(row, X_2, i);
            gsl_vector_add(v, row);
          }

          for(i = 0; i < theta_2->size2; ++i) {
            sumTheta += gsl_vector_get(v, i);
          }

          sumError = 0;
          for(i = 0; i < error_2->size1; ++i) {
            for(j = 0; j < error_2->size2; ++j) {
              sumError += gsl_matrix_get(error_2, i, j);
            }
          }

          gsl_vector_free(v);
          gsl_vector_free(row);
          gsl_matrix_free(error);
          gsl_matrix_free(error_2);
          gsl_matrix_free(X_2);
          gsl_matrix_free(theta_2);

          return 1/2 * sumError + (lambda/2) * sumX + (lambda/2) * sumTheta;
        }

        gsl_matrix* MovieRecommender::computeError() {

          cout << "info m_ratings" << endl;
          cout << "rows" << m_ratings->size1 << endl;
          cout << "columns" << m_ratings->size2 << endl << endl;

          cout << "info m_datas" << endl;
          cout << "rows" << m_parser->getDatas()->size1 << endl;
          cout << "columns" << m_parser->getDatas()->size2 << endl;

          //computeError() = N*-N
          gsl_matrix* copy;

          copy = gsl_matrix_alloc(this->m_ratings->size1, this->m_ratings->size2);
          predict();
          gsl_matrix_memcpy(copy, this->m_ratings);
          //la différence ne pouvant pas jouer sur les valeurs non prédites
          //on remet a 0 celles non notés dans la copie de N*
          for (unsigned int i = 0; i < this->m_parser->getDatas()->size1; i++){
            for (unsigned int j = 0; j < this->m_parser->getDatas()->size2; j++){
              if (gsl_matrix_get(this->m_parser->getDatas(), i, j) == 0)
              gsl_matrix_set(copy,i,j,0);
            }
          }
          gsl_matrix_sub(copy, this->m_parser->getDatas());

          return copy;
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
          cout << "Theta" << endl;
          for (unsigned int i = 0; i < m_theta->size1; i++){
            for (unsigned int j = 0; j < m_theta->size2; j++){
              cout << "|" << gsl_matrix_get(m_theta, i ,j);
            }
            cout << "|" << endl;
          }
          cout << "X" << endl;
          for (unsigned int i = 0; i < m_X->size1; i++){
            for (unsigned int j = 0; j < m_X->size2; j++){
              cout << "|" << gsl_matrix_get(m_X, i ,j);
            }
            cout << "|" << endl;
          }

          /* pour test */
          cout << "Predict" << endl;
          for (unsigned int i = 0; i < m_ratings->size1; i++){
            for (unsigned int j = 0; j < m_ratings->size2; j++){
              cout << "|" << gsl_matrix_get(m_ratings, i ,j);
            }
            cout << "|" << endl;
          }
          /* end test */

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

        MovieRecommender::~MovieRecommender() {
          if(m_theta != NULL) {
            gsl_matrix_free(m_theta);
          }
          if(m_X != NULL) {
            gsl_matrix_free(m_X);
          }
          if(m_ratings != NULL) {
            gsl_matrix_free(m_ratings);
          }

          delete(m_parser);
        }
