#include "Vector3.h"

using namespace std;

Vector3::Vector3(){
	this->set(0,0,0);
}

Vector3::Vector3(double x, double y, double z){
	this->set(x,y,z);
}

void Vector3::set(double x, double y, double z){
	m_c[0]=x;
	m_c[1]=y;
	m_c[2]=z;
}

void Vector3::add(double x,double y,double z) {
    m_c[0]+=x;
    m_c[1]+=y;
    m_c[2]+=z;
}

double Vector3::size(){
	sqrt(m_c[0]*m_c[0]+m_c[1]*m_c[1]+m_c[2]*m_c[2]);
}

void Vector3::printV() const {
    cout << "(" << this->x() << "," << this->y() << "," << this->z() << ")" << endl;
}

Vector3::~Vector3(){}
