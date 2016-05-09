#include "Saver.h"
#define TAILLE_MAX 1000

using namespace std;

Saver::Saver() {
  this->m_filename = "mr";
  this->m_theta = NULL;
  this->m_X = NULL;
  this->m_nbMovies = 0;
  this->m_nbUsers = 0;
}

Saver::Saver(string filename) {
	this->m_filename = filename;
	this->m_theta = NULL;
	this->m_X = NULL;
  this->m_nbMovies = 0;
  this->m_nbUsers = 0;
}

void Saver::save(MovieRecommender *object) {
  FILE* theta, *X;
  gsl_matrix *copy_theta, *copy_X;
  string filetheta, fileX;
  stringstream size;

  copy_theta = gsl_matrix_alloc(object->getTheta()->size1, object->getTheta()->size2);
  copy_X = gsl_matrix_alloc(object->getX()->size1, object->getX()->size2);

  gsl_matrix_memcpy(copy_theta, object->getTheta());
  gsl_matrix_memcpy(copy_X, object->getX());

  filetheta = this->m_filename+".theta";
  fileX = this->m_filename+".X";

  theta = NULL;
  X = NULL;

  theta = fopen(filetheta.c_str(), "w+");
  X = fopen(fileX.c_str(), "w+");

  if(theta && X) {
    // on ecrit le nombre de ligne de theta.
    size << copy_theta->size1;
    fputs(size.str().c_str(), theta);

    // on passe à la ligne suivante.
    fputs("\n", theta);

    // on vide le stringstream
    size.str("");

    // on ecrit le nombre de colonne de theta.
    size << copy_theta->size2;
    fputs(size.str().c_str(), theta);

    // on passe à la ligne suivante.
    fputs("\n", theta);

    // on ecrit la matrice theta dans le fichier
    gsl_matrix_fwrite(theta, copy_theta);

    // on vide le stringstream
    size.str("");

    // on ecrit le nombre de ligne de X.
    size << copy_X->size1;
    fputs(size.str().c_str(), X);

    // on passe à la ligne suivante.
    fputs("\n", X);

    // on vide le stringstream
    size.str("");

    // on ecrit le nombre de colonne de X.
    size << copy_X->size2;
    fputs(size.str().c_str(), X);

    // on passe à la ligne suivante.
    fputs("\n", X);

    // on ecrit la matrice X dans le fichier
    gsl_matrix_fwrite(X, copy_X);

    fclose(theta);
    fclose(X);
  }
  else {
    cout << "ERROR: cannot open file" << endl;
  }

  gsl_matrix_free(copy_theta);
  gsl_matrix_free(copy_X);
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
    // sauvegarde du nombre de films
    this->m_nbUsers = m;
		fgets(chaine, TAILLE_MAX, theta);
		int n = atoi(chaine) ;

    this->m_theta = gsl_matrix_alloc(m,n);

    gsl_matrix_fread(theta, m_theta);

    fgets(chaine, TAILLE_MAX, X);
		m = atoi(chaine);
    // sauvegarde du nombre d'utilisteurs
    this->m_nbMovies = m;
		fgets(chaine, TAILLE_MAX, X);
	  n = atoi(chaine) ;

		this->m_X = gsl_matrix_alloc(m,n);

		gsl_matrix_fread(X, m_X);
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

int Saver::getNbMovies(){
  return this->m_nbMovies;
}

int Saver::getNbUsers(){
  return this->m_nbUsers;
}

Saver::~Saver() {
  if(this->m_theta != NULL) {
    gsl_matrix_free(this->m_theta);
  }

  if(this->m_X != NULL) {
    gsl_matrix_free(this->m_X);
  }
}
