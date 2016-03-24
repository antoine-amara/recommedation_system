#include "Validator.h"

using namespace std;

Validator::Validator() {
	this->m_nbTestSets = 5;
	Saver s = Saver();
	this->m_movieRecommender = MovieRecommender(s);
	this->m_errors = vector<int>();
}

Validator::Validator(string filename, int nbTestSets) {
	this->m_nbTestSets = nbTestSets;
	Saver s = Saver(filename);
	this->m_movieRecommender = MovieRecommender(s);
	this->m_errors = vector<int>();
}

void Validator::start(){
	for(int i=0; i < this->m_nbTestSets; i++){
		string name = "u."+to_string(i);
		computeError(name);
	}
	printReport();
}

void Validator::computeError(string dataset){
	DataParser* d = new DataParser(this->m_movieRecommender.getX()->size1, this->m_movieRecommender.getTheta()->size1);
	Vector3* dTest = d->parseTest();
	int errorCount = 0;

	for(int i = 0; i < d->getN(); i++){
		int mark = gsl_matrix_get(m_movieRecommender.predict(),dTest[i].x(),dTest[i].y());
		if(mark != dTest[i].z())
			errorCount++;
	}

	this->m_errors.push_back(errorCount);

	delete(d);
}

int Validator::computeGlobalError(){
	int taille = this->m_errors.size();
	int GlobalError = accumulate(this->m_errors.begin(), this->m_errors.end(),0);
	GlobalError /= taille;

	return GlobalError;
}

void Validator::printReport(){
	for(unsigned int i = 0; i < this->m_errors.size(); i++){
		cout << "DataSet :" << i;
		cout << "Error :" << this->m_errors[i] << endl;
	}
	cout << endl;
	cout << "TotalDataSet :" << this->m_nbTestSets;
	cout << "GlobalError :" << computeGlobalError() << endl;

}

Validator::~Validator(){
}
