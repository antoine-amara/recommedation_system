#include "DataParser.h"

using namespace std;

DataParser::DataParser() {
}

DataParser::DataParser(string filename) {
}

void DataParser::parse() {
}

void DataParser::parseDatas(int nbMovies, int nbUsers) {

	int i j;
	string file = m_filename+".base";
	ifstream set(file, ios::in)
	int idM, idU, Mark;
	gsl_matrix m_datas * = gsl_matrix_alloc(nbMovies,nbUsers);

	for (i = 0; i < nbMovies; i++){
		for (j=0; j < nbUsers < j++){
			if (idM == i && idU == j)
				idM = ;
				idU = ;
				gsl_matrix_set(m_datas, i, j, Mark);
			else
				gsl_matrix_set(m_datas, i, j, -1);
		}
	}

}

void DataParser::parseGenres() {
}

void DataParser::parseMovies() {
}

gsl_matrix DataParser::getDatas() {
}

vector<string> DataParser::getGenres() {
}

vector<string> DataParser::getMovies() {
}

DataParser::~DataParser() {
	gsl_matrix_free(m_datas);
}
