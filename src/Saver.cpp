#include "Saver.h"
#define TAILLE_MAX 1000

using namespace std;

Saver::Saver() {
  this->m_filename = "mr";
  this->m_theta = NULL;
  this->m_X = NULL;
}

Saver::Saver(string filename) {
	this->m_filename = filename;
	this->m_theta = NULL;
	this->m_X = NULL;
}

void Saver::save(MovieRecommender object) {
  FILE* theta, *X;
  string filetheta, fileX;
  stringstream size;

  filetheta = this->m_filename+".theta";
  fileX = this->m_filename+".X";

  theta = NULL;
  X = NULL;

  theta = fopen(filetheta.c_str(), "w+");
  X = fopen(fileX.c_str(), "w+");

  if(theta && X) {
    // on ecrit le nombre de ligne de theta.
    size << object.getTheta()->size1;
    fputs(size.str().c_str(), theta);

    // on passe à la ligne suivante.
    fputs("\n", theta);

    // on vide le stringstream
    size.str("");

    // on ecrit le nombre de colonne de theta.
    size << object.getTheta()->size2;
    fputs(size.str().c_str(), theta);

    // on passe à la ligne suivante.
    fputs("\n", theta);

    // on ecrit la matrice theta dans le fichier
    gsl_matrix_fprintf(theta, object.getTheta(), "%f");

    // on vide le stringstream
    size.str("");

    // on ecrit le nombre de ligne de X.
    size << object.getX()->size1;
    fputs(size.str().c_str(), X);

    // on passe à la ligne suivante.
    fputs("\n", X);

    // on vide le stringstream
    size.str("");

    // on ecrit le nombre de colonne de X.
    size << object.getX()->size2;
    fputs(size.str().c_str(), X);

    // on passe à la ligne suivante.
    fputs("\n", X);

    // on ecrit la matrice X dans le fichier
    gsl_matrix_fprintf(X, object.getX(), "%f");

    fclose(theta);
    fclose(X);
  }
  else {
    cout << "ERROR: cannot open file" << endl;
  }
}

void Saver::load() {
	FILE* theta, *X;
  string filetheta, fileX;
	char chaine[TAILLE_MAX] = "";

  filetheta = this->m_filename+".theta";
  fileX = this->m_filename+".X";

  theta = NULL;
  X = NULL;

	theta = fopen(filetheta.c_str(),"r");
  X = fopen(fileX.c_str(),"r");

	if (theta && X){
		fgets(chaine, TAILLE_MAX, theta);
		int m = atoi(chaine);
    cout << m << endl;
		fgets(chaine, TAILLE_MAX, theta);
		int n = atoi(chaine) ;
    cout << n << endl;

    this->m_theta = gsl_matrix_alloc(m,n);

    gsl_matrix_fscanf(theta, m_theta);

    fgets(chaine, TAILLE_MAX, X);
		m = atoi(chaine);
    cout << m << endl;
		fgets(chaine, TAILLE_MAX, X);
	  n = atoi(chaine) ;
    cout << n << endl;

		this->m_X = gsl_matrix_alloc(m,n);

		gsl_matrix_fscanf(X, m_X);
	}
	else
		cout << "ERROR : Cannot open file" << endl;
	fclose(theta);
  fclose(X);
}

gsl_matrix* Saver::getTheta() {
  return this->m_theta;
}

gsl_matrix* Saver::getX() {
  return this->m_X;
}

Saver::~Saver() {
  if(this->m_theta != NULL) {
    gsl_matrix_free(this->m_theta);
  }

  if(this->m_X != NULL) {
    gsl_matrix_free(this->m_X);
  }
}
