#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <string>
#include <vector>
#include <gsl/gsl_matrix.h>

#include "ParserInterface.h"

class DataParser : public ParserInterface {

public:
  DataParser();
  DataParser(string filename);
  void parse();
  void parseDatas();
  void parseGenres();
  void parseMovies();
  gsl_matrix getDatas();
  std::vector<string> getGenres();
  std::vector<string> getMovies();

protected:
  string m_filename;
  gsl_matrix m_datas;
  std::vector<string> m_genres;
  std::vector<string> m_movies;
};

#endif
