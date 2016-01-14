#include "DataParser.h"

using namespace std;

DataParser::DataParser(int nbMovies, int nbUsers) {
  this->m_filename = "u";
  m_datas = gsl_matrix_alloc(nbMovies, nbUsers);
  this->m_nbMovies = nbMovies;
  this->m_nbUsers = nbUsers;
}

DataParser::DataParser(string filename, int nbMovies, int nbUsers) {
  this->m_filename = filename;
  m_datas = gsl_matrix_alloc(nbMovies, nbUsers);
  this->m_nbMovies = nbMovies;
  this->m_nbUsers = nbUsers;
}

void DataParser::parse() {
  parseDatas();
  parseGenres();
  parseMovies();
}

void DataParser::parseDatas() {

  int i, j;
  string file = m_filename+".base";
  ifstream set(file.c_str(), ios::in);
  int idM, idU, Mark;
  string data;

  if (set) {
    set >> data;
    idM = stoi(data);
    set >> data;
    idU = stoi(data);
    set >> data;
    Mark = stoi(data);

    for (i = 0; i < this->m_nbMovies; i++){
      for (j=0; j < this->m_nbUsers; j++){
        if (idM == i && idU == j){
          gsl_matrix_set(m_datas, i, j, Mark);
          set >> data;
          idM = stoi(data);
          set >> data;
          idU = stoi(data);
          set >> data;
          Mark = stoi(data);
        }
        else
        gsl_matrix_set(m_datas, i, j, 0);
      }
    }
  }
  else {
    cout << "ERROR: cannot open dataset" << endl;
  }
  set.close();
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
  set.close();
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
  set.close();
}

gsl_matrix* DataParser::getDatas() {
  return m_datas;
}

vector<string> DataParser::getGenres() {
  return m_genres;
}

vector<string> DataParser::getMovies() {
  return m_movies;
}

DataParser::~DataParser() {
  gsl_matrix_free(m_datas);
}
