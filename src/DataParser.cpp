#include "DataParser.h"

using namespace std;

DataParser::DataParser() {
  this->m_filename = "u";
}

DataParser::DataParser(string filename) {
  this->m_filename = filename;
}

void DataParser::parse() {
  parseDatas();
  parseGenres();
  parseMovies();
}

void DataParser::parseDatas() {
}

void DataParser::parseGenres() {
  string file = m_filename+".genre";
  ifstream set(file.c_str(), ios::in);

  if(set) {
    string line;
    string separator = "|";

    while(getline(set, line)) {
      m_genres.push_back(line.substr(0, line.find(separator)));
    }
  }
  else {
    cout << "ERROR: cannot open dataset" << endl;
  }
}

void DataParser::parseMovies() {
  string file = m_filename+".item";
  ifstream set(file.c_str(), ios::in);

  if(set) {
    string line;
    string separator = "|";

    while(getline(set, line)) {
      m_movies.push_back(line.substr(0, line.find(separator)));
    }
  }
  else {
    cout << "ERROR: cannot open dataset" << endl;
  }
}

gsl_matrix DataParser::getDatas() {
  return m_datas;
}

vector<string> DataParser::getGenres() {
  return m_genres;
}

vector<string> DataParser::getMovies() {
  return m_movies;
}

DataParser::~DataParser() {
}
