#include "MovieRecommender.h"
#include "Saver.h"

using namespace std;

MovieRecommender::MovieRecommender(int nbMovies, int nbUsers) {
  this->m_theta = NULL;
  this->m_X = NULL;
  this->m_ratings = gsl_matrix_alloc(nbMovies, nbUsers);
  this->m_parser = DataParser(nbMovies, nbUsers);
  m_parser.parse();
}

MovieRecommender::MovieRecommender(string dataset, int nbMovies, int nbUsers) {
  this->m_theta = NULL;
  this->m_X = NULL;
  this->m_ratings = gsl_matrix_alloc(nbMovies, nbUsers);
  this->m_parser = DataParser(dataset, nbMovies, nbUsers);
  m_parser.parse();
}

MovieRecommender::MovieRecommender(string dataset, int nbMovies, int nbUsers, gsl_matrix* theta, gsl_matrix* X) {
  this->m_theta = theta;
  this->m_X = X;
  this->m_ratings = gsl_matrix_alloc(nbMovies, nbUsers);
  this->m_parser = DataParser(dataset, nbMovies, nbUsers);
  m_parser.parse();
}

MovieRecommender::MovieRecommender(string dataset, Saver saver) {
  saver.load();
  this->m_theta = saver.getTheta();
  this->m_X = saver.getX();
  this->m_ratings = gsl_matrix_alloc(saver.getNbMovies(), saver.getNbUsers());
  this->m_parser = DataParser(dataset, saver.getNbMovies(), saver.getNbUsers());
  m_parser.parse();
}

void MovieRecommender::train(double alpha, double lambda) {
  double threshold = 0.1;
  gsl_matrix *error;
  gsl_matrix *regularizationX, *regularizationtheta;
  gsl_matrix *intermediateX, *intermediatetheta;

  regularizationX = gsl_matrix_alloc(this->m_X->size1, this->m_X->size2);
  intermediateX = gsl_matrix_alloc(this->m_X->size1, this->m_X->size2);

  regularizationtheta = gsl_matrix_alloc(this->m_theta->size1, this->m_theta->size2);
  intermediatetheta = gsl_matrix_alloc(this->m_theta->size1, this->m_theta->size2);

  while(computeCost() > threshold) {
    error = computeError();

    // on calcule la nouvelle matrice X(on effectue la decente de gradient)
    gsl_matrix_memcpy(regularizationX, this->m_X);
    gsl_matrix_scale(regularizationX, lambda);
    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, error, m_theta, 0.0, intermediateX);
    gsl_matrix_add(intermediateX, regularizationX);
    gsl_matrix_scale(intermediateX, alpha);
    gsl_matrix_sub(m_X, intermediateX);

    // on calcule la nouvelle matrice theta(on effectue la decente de gradient)
    gsl_matrix_memcpy(regularizationtheta, this->m_theta);
    gsl_matrix_scale(regularizationtheta, lambda);
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, error, m_X, 0.0, intermediatetheta);
    gsl_matrix_add(intermediatetheta, regularizationtheta);
    gsl_matrix_scale(intermediatetheta, alpha);
    gsl_matrix_sub(m_theta, intermediatetheta);
  }

  saveState("train_result");

  gsl_matrix_free(error);
  gsl_matrix_free(regularizationX);
  gsl_matrix_free(regularizationtheta);
  gsl_matrix_free(intermediateX);
  gsl_matrix_free(intermediatetheta);
}

void MovieRecommender::predict() {

  // transposition m_X
  int mX = this->m_X->size1;
  int mY = this->m_X->size2;
  gsl_matrix* m_X_t;
  m_X_t = gsl_matrix_alloc(mY,mX);
  gsl_matrix_transpose_memcpy(m_X_t, this->m_X);

  //(m_theta)*(m_X_t)
  gsl_blas_dgemm(CblasNoTrans,CblasNoTrans,
                1.0, m_theta,m_X_t,
                0.0, m_ratings);
}

vector<string> MovieRecommender::recommend(int user, int nbMovies) {
}

double MovieRecommender::computeCost() {

}

gsl_matrix* MovieRecommender::computeError() {
  gsl_matrix* copy;

  copy = gsl_matrix_alloc(this->m_ratings->size1, this->m_ratings->size2);

  predict();
  gsl_matrix_memcpy(copy, this->m_ratings);
  gsl_matrix_sub(copy, this->m_parser.getDatas());

  return copy;
}

void MovieRecommender::saveState(string filename) {
  Saver saver = Saver(filename);
  saver.save(*this);
}

void MovieRecommender::loadState(string filename) {
}

void MovieRecommender::printState() {
}

void MovieRecommender::setDatas(string set) {
}

gsl_matrix* MovieRecommender::getTheta() {
  return this->m_theta;
}

gsl_matrix* MovieRecommender::getX() {
  return this->m_X;
}

MovieRecommender::~MovieRecommender() {
  gsl_matrix_free(m_ratings);
}
