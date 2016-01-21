#include "Saver.h"

using namespace std;

Saver::Saver() {
  this->m_filename = "mr.save";
  this->m_theta = NULL;
  this->m_X = NULL;
}

Saver::Saver(string filename) {
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
