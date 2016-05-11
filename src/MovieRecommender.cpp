#include "MovieRecommender.h"
#include "Saver.h"

using namespace std;

MovieRecommender::MovieRecommender() {}

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

MovieRecommender::MovieRecommender(Saver saver) {
  saver.load();
  this->m_theta = gsl_matrix_alloc(saver.getTheta()->size1, saver.getTheta()->size2);
  gsl_matrix_memcpy (this->m_theta, saver.getTheta());
  this->m_X = gsl_matrix_alloc(saver.getX()->size1, saver.getX()->size2);
  gsl_matrix_memcpy (this->m_X, saver.getX());
  this->m_nbMovies = saver.getNbMovies();
  this->m_nbUsers = saver.getNbUsers();
  m_parser = NULL;
}

void MovieRecommender::train(double alpha, double lambda, int save) {
  bool firstIteration;
  double cost, oldcost, testcost, oldtestcost;
  int i;
  gsl_matrix *error;
  gsl_matrix *regularizationX, *regularizationtheta;
  gsl_matrix *intermediateX, *intermediatetheta;

  i = save;

  cost = computeCost(TRAINSET, lambda);
  testcost = computeCost(TESTSET, lambda);
  oldcost = 0.0;
  oldtestcost = 0.0;
  firstIteration = true;

  regularizationX = gsl_matrix_alloc(this->m_X->size1, this->m_X->size2);
  intermediateX = gsl_matrix_alloc(this->m_X->size1, this->m_X->size2);

  regularizationtheta = gsl_matrix_alloc(this->m_theta->size1, this->m_theta->size2);
  intermediatetheta = gsl_matrix_alloc(this->m_theta->size1, this->m_theta->size2);

  while(!(cost < oldcost && testcost > oldtestcost) || firstIteration) {
    error = gsl_matrix_alloc(m_X->size1, m_theta->size1);
    // on calcule les erreurs comises par le système
    gsl_spmatrix_sp2d(error, computeTrainError());


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

    oldcost = cost;
    oldtestcost = testcost;
    cost = computeCost(TRAINSET, lambda);
    testcost = computeCost(TESTSET, lambda);
    printState(lambda);

    cout << "cost state" << endl;
    cout << "cost: " << cost << " oldcost: " << oldcost << endl;
    cout << "testcost" << testcost << " oldtestcost: " << oldtestcost << endl;
    cout << (cost < oldcost && testcost > oldtestcost) << endl;

    if(firstIteration) {
      firstIteration = false;
    }

    if(cost > oldcost) {
      // on diminue alpha
      cout << "minus alpha" << endl;
      alpha /= 10.0;
      cout << alpha << endl;
    }
    else {
      cout << "alpha x 2" << endl;
      //on augmente alpha
      alpha *= 2.0;
      cout << alpha << endl;
    }

    if(i == 0) {
      cout << "saving ..." << endl;
      saveState("data/save_train");
      i = save;
    }
    else {
      i--;
    }
    gsl_matrix_free(error);
  }

  cout << "end gradient decent saving ..." << endl;

  saveState(m_parser->getFilename());

  gsl_matrix_free(regularizationX);
  gsl_matrix_free(regularizationtheta);
  gsl_matrix_free(intermediateX);
  gsl_matrix_free(intermediatetheta);
}

gsl_matrix* MovieRecommender::predict() {
  gsl_matrix *ratings;

  ratings = gsl_matrix_alloc(m_nbMovies, m_nbUsers);

  //(m_theta)*(m_X_t)
  gsl_blas_dgemm(CblasNoTrans,CblasTrans,
    1.0, m_X, m_theta,
    0.0, ratings);

    return ratings;
  }

  gsl_matrix* MovieRecommender::normalize() {
    gsl_matrix* m = predict();
    unsigned int i, j;

    for(i = 0; i < m->size1; ++i) {
      for(j = 0; j < m->size2; ++j) {
        int value = round(gsl_matrix_get(m, i, j));
        if(value > 5) {
          value = 5;
        }
        gsl_matrix_set(m, i, j, (double)value);
      }
    }

    return m;
  }

  int MovieRecommender::round(double a) {
    double decimal;
    int res;

    if(a < 0) {
      decimal = a - ceil(a);
      if(decimal < -0.5) res = ceil(a);
      else res = floor(a);
    }
    else {
      decimal = a - floor(a);
      if(decimal < 0.5) res = floor(a);
      else res = ceil(a);
    }

    return res;
  }

  vector<string> MovieRecommender::recommend(unsigned int user, int nbMovies) {
    vector<string> movies;
    unsigned int bestMovie;
    const gsl_rng_type *T;
    gsl_rng* r;
    int randMovie, randN;
    unsigned int i;
    gsl_matrix* Netoile;
    gsl_spmatrix* fives, *N;
    int fivesLength;

    Netoile = normalize();
    N = m_parser->getDatas();
    fives = gsl_spmatrix_alloc(1, Netoile->size1);

    gsl_vector *userRates = gsl_vector_alloc(N->size1);
    gsl_vector *bestMovieVec = gsl_vector_alloc(m_X->size2);
    gsl_vector* movie = gsl_vector_alloc(m_X->size2);

    fivesLength = 0;
    for(i = 0; i < N->nz; ++i) {
      if(N->p[i] == user) {
        if(N->data[i] == 5 || N->data[i] == 4) {
          gsl_spmatrix_set(fives, 1, fivesLength, N->i[i]);
          fivesLength++;
        }
      }
    }

    gsl_rng_env_setup();
    //to get real random each time
    gsl_rng_default_seed = time(0);

    T = gsl_rng_taus;
    r = gsl_rng_alloc(T);

    randN = gsl_rng_uniform_int(r, (fivesLength-1));
    bestMovie = gsl_spmatrix_get(N, 1, randN);

    gsl_matrix_get_row(bestMovieVec, m_X, bestMovie);

    randMovie = gsl_rng_uniform_int(r, (m_X->size1-2));
    i =  randMovie;
    i++;
    while(nbMovies != 0) {
      if (i== (unsigned int)round(randMovie)) {
        break;
      }

      if(i == m_X->size1-1) {
        i = 0;
      }

      if(i == bestMovie) {
        i++;
        continue;
      }

      gsl_matrix_get_row(movie, m_X, i);
      gsl_vector_sub(movie, bestMovieVec);

      double sum = 0;
      for(unsigned int j = 0; j < movie->size; ++j) {
        sum += gsl_vector_get(movie, j);
      }

      if(round(abs(sum)) == 0) {
        movies.push_back("Titre : " + m_parser->getMovies()[i] + " | Note : " + std::to_string(gsl_matrix_get(Netoile, i, user)));
        nbMovies--;
      }
      i++;
    }

    gsl_vector_free(userRates);
    gsl_vector_free(bestMovieVec);
    gsl_vector_free(movie);
    gsl_matrix_free(Netoile);

    gsl_rng_free(r);

    return movies;
  }

  double MovieRecommender::computeCost(int mode, double lambda) {
    unsigned int i, j;
    double sumX, sumTheta, sumError;
    double N;
    gsl_spmatrix* error;

    N = m_parser->getN() + 0.0;

    sumX = 0;
    sumTheta = 0;
    sumError = 0;

    if(mode == TRAINSET) {
      error = computeTrainError();
    }
    else{
      //Pour le cout du test il faut ajuster N à 20% ce qui correspond à la taille d'un test.
      //L'entrainement représente 80% (le N actuel) donc on fait N*25% pour obtenir ces 20%
      N = m_parser->getN() * 25.0 / 100.0;
      error = computeTestError();
    }


      /*
      * Deuxieme Element *
      */
      gsl_matrix *X_2 = gsl_matrix_alloc(m_X->size2, m_X->size2);
      gsl_blas_dgemm(CblasTrans,CblasNoTrans,
        1.0, m_X, m_X,
        0.0, X_2);

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



          /* sommes des éléments */
          for(i = 0; i < theta_2->size1; ++i) {
            for(j = 0; j < theta_2->size2; ++j) {
              sumTheta += gsl_matrix_get(theta_2, i, j);
            }
          }

          for(i  = 0; i < error->nz; ++i) {
            sumError += pow(gsl_spmatrix_get(error, error->i[i], error->p[i]), 2);
          }

          gsl_spmatrix_free(error);
          gsl_matrix_free(X_2);
          gsl_matrix_free(theta_2);

          return sqrt(1.0/N * sumError) + (lambda/N) * sumX + (lambda/N) * sumTheta;
        }

        gsl_spmatrix* MovieRecommender::computeTrainError() {
          gsl_matrix* Netoile;
          gsl_spmatrix* error;
          unsigned int i;

          Netoile = predict();

          error = gsl_spmatrix_alloc(m_parser->getDatas()->size1, m_parser->getDatas()->size2);

          gsl_spmatrix_memcpy(error, m_parser->getDatas());

          for(i = 0; i < error->nz; ++i) {
            int e;
            e = gsl_matrix_get(Netoile, error->i[i], error->p[i]) - error->data[i];
            gsl_spmatrix_set(error, error->i[i], error->p[i], e);
          }

          gsl_matrix_free(Netoile);

          return error;
        }

        gsl_spmatrix* MovieRecommender::computeTestError() {
          Vector3 testdatas[m_parser->getN()];// N
          gsl_matrix* ratings;
          gsl_spmatrix *result;
          int i;

          ratings = NULL;

          ratings = predict(); // N*

          result = gsl_spmatrix_alloc(ratings->size1, ratings->size2); //N* - N

          m_parser->parseTest(testdatas, m_parser->getN());

          for(i = 0; i < m_parser->getN(); ++i) {
            int error;
            error = gsl_matrix_get(ratings, testdatas[i].x(), testdatas[i].y()) - testdatas[i].z();
            gsl_spmatrix_set(result, testdatas[i].x(), testdatas[i].y(), error);
          }

          gsl_matrix_free(ratings);

          return result;
        }

        void MovieRecommender::saveState(string filename) {
          Saver saver = Saver(filename);
          saver.save(this);
        }

        void MovieRecommender::loadState(string filename) {
          Saver saver = Saver(filename);
          saver.load();
        }

        void MovieRecommender::printState(double lambda) {
          //printMatrix("Theta", m_theta);
          //printMatrix("X", m_X);

          cout << "cout d'entrainement: " << computeCost(TRAINSET, lambda) << endl;
          cout << "cout de test: " << computeCost(TESTSET, lambda) << endl;
        }

        void MovieRecommender::setDatas(string set, int nbMovies, int nbUsers) {
          this->m_parser = new DataParser(set, nbMovies, nbUsers);
          m_parser->parse();
        }

        void MovieRecommender::setTestDatas(string set, int nbMovies, int nbUsers, int N) {
          this->m_parser = new DataParser(set, nbMovies, nbUsers);
          this->m_parser->setN(N);
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

          // to get real random each time
          gsl_rng_default_seed = time(0);

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

          gsl_rng_free(r);
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

          if(m_parser != NULL)
            delete(m_parser);
        }
