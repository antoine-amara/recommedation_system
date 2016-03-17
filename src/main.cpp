#include "DataParser.h"
#include "Saver.h"
#include "MovieRecommender.h"
#include <gsl/gsl_matrix.h>
#include <iostream>

using namespace std;


int main(void) {
  int nbMovies, nbUsers, nbGenres;
  //gsl_matrix *theta, *X;
  //gsl_matrix *rates;
  double lambda, alpha;

  nbMovies = 1682;
  nbUsers = 943;
  nbGenres = 19;
  lambda = 5/100;
  alpha = 0.001;

  //rates = gsl_matrix_alloc(nbMovies, nbUsers);
  /*theta = gsl_matrix_alloc(nbUsers, nbGenres);
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
  gsl_matrix_set(X, 4, 2, 1.0);*/

  //Saver s = Saver("train_result");
  MovieRecommender *mr = new MovieRecommender("data/u", nbMovies, nbUsers, nbGenres);
  //gsl_matrix_memcpy(rates, mr->predict());
  mr->train(alpha,lambda);

  /*cout << "user: 1" << " movie: 6" << "rates: " << gsl_matrix_get(rates, 6, 1) << endl;
  cout << "user: 1" << " movie: 10" << "rates: " << gsl_matrix_get(rates, 10, 1) << endl;
  cout << "user: 1" << " movie: 12" << "rates: " << gsl_matrix_get(rates, 12, 1) << endl;
  cout << "user: 1" << " movie: 14" << "rates: " << gsl_matrix_get(rates, 14, 1) << endl;
  cout << "user: 1" << " movie: 17" << "rates: " << gsl_matrix_get(rates, 17, 1) << endl;*/

  //gsl_matrix_free(theta);
  //gsl_matrix_free(X);
  //delete(mr);
  //gsl_matrix_free(rates);

  return 0;
}
