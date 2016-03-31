#include "DataParser.h"

using namespace std;

DataParser::DataParser() {
}

DataParser::DataParser(int nbMovies, int nbUsers) {
  this->m_filename = "u";
  m_datas = gsl_matrix_calloc(nbMovies, nbUsers);
  this->m_nbMovies = nbMovies;
  this->m_nbUsers = nbUsers;
  this->m_N = 0;
}

DataParser::DataParser(string filename, int nbMovies, int nbUsers) {
  this->m_filename = filename;
  m_datas = gsl_matrix_calloc(nbMovies, nbUsers);
  this->m_nbMovies = nbMovies;
  this->m_nbUsers = nbUsers;
  this->m_N = 0;
}

void DataParser::parse() {
  parseDatas();
  parseGenres();
  parseMovies();
}

void DataParser::parseDatas() {

  string file = m_filename+".base";
  ifstream set(file.c_str(), ios::in);
  int idM, idU, Mark;
  string data;

  if (set) {
    // on consomme l'id de l'utilisateur.
    set >> data;
    idU = stoi(data) - 1;
    // on consomme l'id du film.
    set >> data;
    idM = stoi(data) - 1;
    // on consomme la note du film.
    set >> data;
    Mark = stoi(data);
    // on consomme le timestamp.
    set >> data;

    m_N++;

    while(!set.eof()) {

      // les indices de la matrice sont décalée par rapport aux indices des films et utilisateurs.
      gsl_matrix_set(m_datas, idM, idU, Mark);
      // on consomme l'id du film.
      set >> data;
      idU = stoi(data) - 1;
      // on consomme l'id de l'utilisateur.
      set >> data;
      idM = stoi(data) - 1;
      // on consomme la note du film.
      set >> data;
      Mark = stoi(data);
      // on consomme le timestamp.
      set >> data;

      m_N++;
    }
  }
  else {
    cout << "ERROR: cannot open dataset" << endl;
  }
  set.close();
  m_N--;
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
    char separator = '|';
    vector<string> subline;

    while(getline(set, line)) {
      subline = split(line, separator);
      this->m_movies.push_back(subline[1]);
    }
  }
  else {
    cout << "ERROR: cannot open dataset" << endl;
  }
  set.close();
}

void DataParser::parseTest(Vector3* d, int N) {
  string file = m_filename+".test";
  ifstream set(file.c_str(), ios::in);
  int idM, idU, Mark;
  string data;
  int i = 0;

  m_N = N;

  d[m_N] = Vector3();

  if (set) {
    // on consomme l'id de l'utilisateur.
    set >> data;
    idU = stoi(data) - 1;
    // on consomme l'id du film.
    set >> data;
    idM = stoi(data) - 1;
    // on consomme la note du film.
    set >> data;
    Mark = stoi(data);
    // on consomme le timestamp.
    set >> data;

    while(!set.eof()) {

      // les indices de la matrice sont décalée par rapport aux indices des films et utilisateurs.
      d[i].set(idM, idU, Mark);
      // on consomme l'id du film.
      set >> data;
      idU = stoi(data) - 1;
      // on consomme l'id de l'utilisateur.
      set >> data;
      idM = stoi(data) - 1;
      // on consomme la note du film.
      set >> data;
      Mark = stoi(data);
      // on consomme le timestamp.
      set >> data;

      i++;
    }
  }
  else {
    cout << "ERROR: cannot open dataset" << endl;
  }
  set.close();
}

vector<string> DataParser::split(string str, char separator) {
  vector<string> internal;
  stringstream ss(str); // On transforme la chaine en stream.
  string tok;

  while(getline(ss, tok, separator)) {
    internal.push_back(tok);
  }

  return internal;
}

gsl_matrix* DataParser::getDatas() {
  return m_datas;
}

int DataParser::getN() {
  return m_N;
}

void DataParser::setN(int N) {
  this->m_N = N;
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
