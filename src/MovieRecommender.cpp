#include "MovieRecommender.h"
#include "Saver.h"

using namespace std;

MovieRecommender::MovieRecommender(string dataset, int nbMovies, int nbUsers) {
  this->m_theta = NULL;
  this->m_X = NULL;
  this->m_ratings = NULL;
  this->m_parser = DataParser(nbMovies, nbUsers);
}

MovieRecommender::MovieRecommender(string dataset, int nbMovies, int nbUsers) {
  this->m_theta = NULL;
  this->m_X = NULL;
  this->m_ratings = NULL;
  this->m_parser = DataParser(dataset, nbMovies, nbUsers);
}

MovieRecommender::MovieRecommender(string dataset, int nbMovies, int nbUsers, gsl_matrix* theta, gsl_matrix* X) {
  this->m_theta = theta;
  this->m_X = X;
  this->m_ratings = NULL;
  this->m_parser = DataParser(dataset, nbMovies, nbUsers);
}

MovieRecommender::MovieRecommender(string dataset, Saver saver) {
  saver.load();
  this->m_theta = saver.getTheta();
  this->m_X = saver.getX();
  this->m_ratings = NULL;
  this->m_parser = DataParser(dataset, save.getNbMovies, save.getNbUsers);
}

void MovieRecommender::train(double alpha) {
}

void MovieRecommender::predict() {
}

vector<string> MovieRecommender::recommend() {
}

double MovieRecommender::computeCost() {
}

void MovieRecommender::saveState(string filename) {
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
}
