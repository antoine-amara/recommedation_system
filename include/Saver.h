#ifndef SAVER_H
#define SAVER_H

#include <string>
#include <gsl/gsl_matrix.h>

#include "MovieRecommender.h"

class Saver {

public:
  Saver();
  Saver(std::string filename);
  void save(MovieRecommender object);
  void load();
  gsl_matrix* getTheta();
  gsl_matrix* getX();
  double getAlpha();

protected:
  string m_filename;
  gsl_matrix* m_theta;
  gsl_matrix* m_X;
  double m_alpha;
};

#endif
