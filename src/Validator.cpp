#include "Validator.h"

using namespace std;

Validator::Validator(){
	this->m_nbTestSets = 5;
	this->m_movieRecommender = MovieRecommender("u");
	//this->m_errors = vector<int>();
}

Validator::Validator(string filename, int nbTestSets){
	this->m_nbTestSets = nbTestSets;
	this->m_movieRecommender = MovieRecommender(filename);
	//this->m_errors = vector<int>();
}

void Validator::start(){
	for(unsigned int i=0; i < this->m_nbTestSets; i++){
		computeError("u"+toString(i));
	}
	printReport();
}

void Validator::computeError(string dataset){
	DataParser d = new DataParser(this->m_movieRecommender.getX().size2, this->m_movieRecommender.getTheta().size2);
	d.parse();
	Vector3 dTest = d.parseTest();
	int errorCount = 0;

	for(unsigned int i = 0; i < dTest.size(); i++){
		double mark = gsl_matrix_get(m_movieRecommender.predict(),dTest.getY(),dTest.getX());
		if(mark != dTest.getZ())
			errorCount++;
	}

	this->m_errors.push_back(errorCount);

	delete(d);
}

int Validator::computeGlobalError(){
	int taille = this.m_errors.size();
	int GlobalError = accumulate(this->m_errors.begin(), this->m_errors.end(),0);
	GlobalError /= taille;
	
	return GlobalError;
}

void printReport(){
	for(unsigned int i = 0; i < m_errors.size(); i++){
		cout << "DataSet :" << i;
		cout << "Error :" << m_errors[i] << endl;
	}
	cout << endl;
	cout << "TotalDataSet :" << m_nbTestSets;
	cout << "GlobalError :" << computeGlobalError << endl;

}

Validator::~Validator(){

}