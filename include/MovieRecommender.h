#ifndef MOVIERECOMMENDER_H
#define MOVIERECOMMENDER_H

#include <string>
#include <vector>
#include <gsl/gsl_matrix.h>

#include "AiInterface.h"
#include "DataParser.h"
#include "Saver.h"

class MovieRecommender : public AiInterface {

public:
  MovieRecommender(int nbMovies, int nbUsers);
  MovieRecommender(std::string dataset, int nbMovies, int nbUsers);
  MovieRecommender(std::string dataset, int nbMovies, int nbUsers, gsl_matrix* theta, gsl_matrix* X);
  MovieRecommender(Saver saver);
  void train(double alpha);
  void predict();
  std::vector<std::string> recommend(int nbMovies);
  double computeCost();
  void saveState();
  void loadState(std::string file);
  void printState();
  void setDatas(std::string set);
  gsl_matrix* getTheta();
  gsl_matrix* getX();
  virtual ~MovieRecommender();

protected:
  gsl_matrix* m_theta;
  gsl_matrix* m_X;
  gsl_matrix* m_ratings;
  DataParser m_parser;
};

#endif
