#include "Saver.h"
#define TAILLE_MAX 1000

using namespace std;

Saver::Saver() {
  this->m_filename = "mr.save";
  this->m_theta = NULL;
  this->m_X = NULL;
}

Saver::Saver(string filename) {
	this->m_filename = filename;
	this->m_theta = NULL;
	this->m_X = NULL;
}

void Saver::save(MovieRecommender object) {
  FILE* file;
  stringstream size;

  file = NULL;

  file = fopen(this->m_filename.c_str(), "w+");

  if(file) {
    // on ecrit le nombre de ligne de theta.
    size << object.getTheta()->size1;
    fputs(size.str().c_str(), file);

    // on ecrit le nombre de colonne de theta.
    size << object.getTheta()->size2;
    fputs(size.str().c_str(), file);

    // on ecrit la matrice theta dans le fichier
    gsl_matrix_fprintf(file, object.getTheta(), "%f");

    fclose(file);
  }
  else {
    cout << "ERROR: cannot open file" << endl;
  }
}

void Saver::load() {
	FILE* fichier;
	char chaine[TAILLE_MAX] = "";

	fichier = fopen(this->m_filename,"r");

	if (fichier != NULL){
		fgets(chaine, TAILLE_MAX, fichier);
		int m = atoi(chaine);
		fgets(chaine, TAILLE_MAX, fichier);
		int n = atoi(chaine) ;

		if (m == NULL || n == NULL)
			this->m_theta = gsl_matrix_alloc(m,n);
		else
			cout << "ERROR : File bad construction in line 1 or 2" << endl;

		gsl_matrix_fscanf(fichier, m_theta);

		fgets(chaine, TAILLE_MAX, fichier);
		int m = atoi(chaine);
		fgets(chaine, TAILLE_MAX, fichier);
		int n = atoi(chaine) ;

		if (m == NULL || n == NULL)
			this->m_X = gsl_matrix_alloc(m,n);
		else
			cout << "ERROR : File bad construction in line 1 or 2" << endl;

		gsl_matrix_fscanf(fichier, m_X);

		if (fgets(chaine, TAILLE_MAX, fichier) != NULL)
			this->m_alpha = atof(chaine);
	}
	else
		cout << "ERROR : Cannot open file" << endl;
	fclose(fichier);
}

gsl_matrix* Saver::getTheta() {
  return this->m_theta;
}

gsl_matrix* Saver::getX() {
  return this->m_X;
}

double Saver::getAlpha() {
  return this->m_alpha;
}

Saver::~Saver() {
  if(this->m_theta != NULL) {
    gsl_matrix_free(this->m_theta);
  }

  if(this->m_X != NULL) {
    gsl_matrix_free(this->m_X);
  }
}
