#include "Saver.h"
#define TAILLE_MAX 1000

using namespace std;

Saver::Saver() {
}

Saver::Saver(string filename) {
	this->m_filename = filename;
	this->m_theta = NULL;
	this->m_X = NULL;
}

void Saver::save(MovieRecommender object) {
}

void Saver::load() {
	FILE* fichier = NULL;
	char chaine[TAILLE_MAX] = "";

	fichier = fopen(this->m_filename,"r");

	if (fichier != NULL){
		fgets(chaine, TAILLE_MAX, fichier);
		int m = atoi(chaine);
		fgets(chaine, TAILLE_MAX, fichier);
		int n = atoi(chaine) ;

		assert(m != NULL && n != NULL);
		this->m_theta = gsl_matrix_alloc(m,n);

		gsl_matrix_fscanf(fichier, m_theta);

		fgets(chaine, TAILLE_MAX, fichier);
		int m = atoi(chaine);
		fgets(chaine, TAILLE_MAX, fichier);
		int n = atoi(chaine) ;

		assert(m != NULL && n != NULL);
		this->m_X = gsl_matrix_alloc(m,n);

		gsl_matrix_fscanf(fichier, m_X);

		if (fgets(chaine, TAILLE_MAX, fichier) != NULL){
			this->m_alpha = atof(chaine);
		}
	}
	else{
		cout << "ERROR : Cannot open file" << endl;
	}
	fclose(fichier);
}

gsl_matrix* Saver::getTheta() {
}

gsl_matrix* Saver::getX() {
}

double Saver::getAlpha() {
}
