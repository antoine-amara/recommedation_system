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

Vector3* DataParser::parseTest() {

  /* BUG: durant l'execution l'adresse du ifstream ne bouge pas XD mais il y a segfault a la deuxieme lecture */
  /* BUG: la variable de type string data est perdu apres insertions dans le Vector3 */

  
  ifstream set(m_filename.c_str(), ios::in);

  set.seekg (0, set.end);
  int length = set.tellg();
  set.seekg (0, set.beg);

  int idM, idU, Mark;
  string data;
  int i = 0;
  Vector3 d[length];
  d[length] = Vector3();

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

    cout << "data before insert: " << data << endl;

    d[i].set(idM, idU, Mark);

    cout << "data after insert" << data << endl;

    while(!set.eof()) {
      cout << "while" << endl;

      // les indices de la matrice sont décalée par rapport aux indices des films et utilisateurs.
      //datas[i].set(idM, idU, Mark);
      // on consomme l'id du film.
      cout << "data before second read: " << data << endl;
      set >> data;
      cout << "data after second read: " << data << endl;
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

  return d;
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

vector<string> DataParser::getGenres() {
  return m_genres;
}

vector<string> DataParser::getMovies() {
  return m_movies;
}

DataParser::~DataParser() {
  gsl_matrix_free(m_datas);
}
