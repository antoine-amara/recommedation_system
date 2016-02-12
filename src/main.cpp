#include "DataParser.h"
#include "Saver.h"
#include "MovieRecommender.h"
#include <gsl/gsl_matrix.h>
#include <iostream>

using namespace std;


int main(void) {
  int nbMovies, nbUsers, nbGenres;
  gsl_matrix *theta, *X, *error;
  double lambda;

  nbMovies = 5;
  nbUsers = 4;
  nbGenres = 3;
  lambda = 0.001;

  theta = gsl_matrix_alloc(nbUsers, nbGenres);
  X = gsl_matrix_calloc(nbMovies, nbGenres);
  error = gsl_matrix_alloc(nbUsers, nbMovies);

  gsl_matrix_set(theta, 0, 0, 1.0);
  gsl_matrix_set(theta, 0, 1, 5.0);
  gsl_matrix_set(theta, 0, 2, 1.0);
  gsl_matrix_set(theta, 1, 0, 1.0);
  gsl_matrix_set(theta, 1, 1, 5.0);
  gsl_matrix_set(theta, 1, 2, 1.0);
  gsl_matrix_set(theta, 2, 0, 1.0);
  gsl_matrix_set(theta, 2, 1, 1.0);
  gsl_matrix_set(theta, 2, 2, 5.0);
  gsl_matrix_set(theta, 3, 0, 1.0);
  gsl_matrix_set(theta, 3, 1, 1.0);
  gsl_matrix_set(theta, 3, 2, 5.0);

  gsl_matrix_set(X, 0, 1, 1.0);
  gsl_matrix_set(X, 1, 1, 1.0);
  gsl_matrix_set(X, 2, 1, 1.0);
  gsl_matrix_set(X, 3, 2, 1.0);
  gsl_matrix_set(X, 4, 2, 1.0);

  MovieRecommender *mr = new MovieRecommender("data/testparser", nbMovies, nbUsers, theta, X);
  error = mr->computeError();
  //mr->predict();
  //mr->printState(lambda);

  cout << "Error" << endl;
  for (unsigned int i = 0; i < error->size1; i++){
    for (unsigned int j = 0; j < error->size2; j++){
      cout << "|" << gsl_matrix_get(error, i ,j);
    }
    cout << "|" << endl;
  }

  gsl_matrix_free(theta);
  gsl_matrix_free(X);
  gsl_matrix_free(error);

  delete(mr);

  return 0;
}
