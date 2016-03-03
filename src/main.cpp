#include "DataParser.h"
#include "Saver.h"
#include "MovieRecommender.h"
#include <gsl/gsl_matrix.h>
#include <iostream>

using namespace std;


int main(void) {
  int nbMovies, nbUsers, nbGenres;
  gsl_matrix *theta, *X;
  double lambda, alpha;

  nbMovies = 5;
  nbUsers = 4;
  nbGenres = 3;
  lambda = 0.0001;
  alpha = 0.001;

  theta = gsl_matrix_alloc(nbUsers, nbGenres);
  X = gsl_matrix_calloc(nbMovies, nbGenres);

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

  Saver s = Saver("train_result");
  MovieRecommender *mr = new MovieRecommender("data/u", nbMovies, nbUsers, theta, X);
  mr->train(alpha, lambda);

  //gsl_matrix_free(theta);
  //gsl_matrix_free(X);

  return 0;
}
