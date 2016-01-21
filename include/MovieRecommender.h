#ifndef MOVIERECOMMENDER_H
#define MOVIERECOMMENDER_H

#include <gsl/gsl_matrix.h>

class MovieRecommender {

public:
  MovieRecommender(gsl_matrix* theta, gsl_matrix* X);
  gsl_matrix* getTheta();
  gsl_matrix* getX();

protected:
  gsl_matrix* m_theta;
  gsl_matrix* m_X;
};

#endif
