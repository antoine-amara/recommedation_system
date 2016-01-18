#include "DataParser.h"
#include <gsl/gsl_matrix.h>
#include <iostream>

using namespace std;

/*********************************************************/
/* Main de test pour le parser de fichier                */
/* Nom du datasets: testparser                           */
/* Le test est basé sur un petit exemple présent dans    */
/* les notes concernant l'algorithme.                    */
/*********************************************************/

int main(void) {
  int nbMovies, nbUsers;
  gsl_matrix* matrix;
  vector<string> genres;
  vector<string> movies;
  unsigned int i, j;

  nbMovies = 5;
  nbUsers = 4;

  DataParser parser = DataParser("testparser", nbMovies, nbUsers);
  parser.parse();

  matrix = parser.getDatas();
  genres = parser.getGenres();
  movies = parser.getMovies();

  cout << endl << "Datas matrix:" << endl;
  for(i = 0; i < nbMovies; ++i) {
    for(j = 0; j < nbUsers; ++j) {
      cout << gsl_matrix_get(matrix, i, j);
    }
    cout << endl;
  }

  cout << endl << "Genres:" << endl;
  for(i = 0; i < genres.size(); ++i) {
    cout << genres[i] << endl;
  }

  cout << endl <<  "Movies:" << endl;
  for(i=0; i < movies.size(); ++i) {
      cout << movies[i] << endl;
  }

  return 0;
}
