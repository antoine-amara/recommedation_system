#include "Saver.h"
#include "MovieRecommender.h"
#include <gsl/gsl_matrix.h>
#include <iostream>

using namespace std;

/*********************************************************/
/* Main de test pour le saver                            */
/* Nom du fichier de sauvegarde: test                    */
/* Le test est basé sur un petit exemple présent dans    */
/* les notes concernant l'algorithme.                    */
/*********************************************************/

int main(void) {
  int nbMovies, nbUsers, nbFeatures;
  gsl_matrix* theta, *X;
  gsl_matrix* thetaload, *Xload;
  unsigned int i, j;

  nbMovies = 5;
  nbUsers = 4;
  nbFeatures = 3;

  theta = gsl_matrix_calloc(nbUsers, nbFeatures);
  X = gsl_matrix_calloc(nbMovies, nbFeatures);

  gsl_matrix_set(theta, 0, 1, 5.0);
  gsl_matrix_set(theta, 1, 1, 5.0);
  gsl_matrix_set(theta, 2, 2, 5.0);
  gsl_matrix_set(theta, 3, 2, 5.0);

  gsl_matrix_set(X, 0, 0, 1.0);
  gsl_matrix_set(X, 0, 1, 1.0);
  gsl_matrix_set(X, 1, 0, 1.0);
  gsl_matrix_set(X, 1, 1, 1.0);
  gsl_matrix_set(X, 2, 0, 1.0);
  gsl_matrix_set(X, 2, 1, 1.0);
  gsl_matrix_set(X, 3, 0, 1.0);
  gsl_matrix_set(X, 3, 2, 1.0);
  gsl_matrix_set(X, 4, 0, 1.0);
  gsl_matrix_set(X, 4, 2, 1.0);

  Saver saver = Saver("test");
  MovieRecommender recommender = MovieRecommender(theta, X);
  saver.save(recommender);
  saver.load();

  thetaload = saver.getTheta();
  Xload = saver.getX();

  cout << "Theta load by saver: " << endl;
  for(i = 0; i < nbUsers; ++i) {
    for(j = 0; j < nbFeatures; ++j) {
      cout << gsl_matrix_get(thetaload, i, j);
    }
    cout << endl;
  }

  cout << "X load by saver: " << endl;
  for(i = 0; i < nbMovies; ++i) {
    for(j = 0; j < nbFeatures; ++j) {
      cout << gsl_matrix_get(Xload, i, j);
    }
    cout << endl;
  }

  return 0;
}
