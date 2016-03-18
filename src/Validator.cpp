#include "Validator.h"

using namespace std;

Validator::Validator(){
	this->m_nbTestSets = 5;
	this->m_movieRecommender = new MovieRecommender("u");
}

Validator::Validator(string filename, int nbTestSets){
	this->m_nbTestSets = nbTestSets;
	this->m_movieRecommender = new MovieRecommender(filename);
}

void Validator::start(){

}

void Validator::computeError(string dataset){
	DataParser d = new DataParser(this->m_movieRecommender.getX().size2, this->m_movieRecommender.getTheta().size2);
	d.parse();
}

void Validator::computeGlobalError(){

}

void printReport(){

}