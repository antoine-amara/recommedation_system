#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

class Vector3{

public:
	/*!
	  *  \brief Constructeur par défaut.
	  *
	  *  Ce constructeur initialisera un Vecteur3 par défaut.
	  *  Les valeurs par défaut seront (0,0,0).
	  */
	Vector3();

	/*!
	  *  \brief Constructeur par défaut.
	  *
	  *  Ce constructeur initialisera un Vecteur3.
	  *  Les valeurs seront (x,y,z).
	  *
	  *  \param x : un double
	  *  \param y : un double
	  *  \param z : un double
	  */
	Vector3(double x, double y, double z);

	/*!
	  *  \brief Set (x,y,z)
	  *
	  *  Défini les éléments (x,y,z) au Vector3.
	  *
	  *  \param x : un double
	  *  \param y : un double
	  *  \param z : un double
	  *
	  */
	void set(double x,double y,double z);

	/*
	 *  \brief accéder au i-ème élément
	 *
	 *  \param i : un int correspondant au i-ème élément.
	 *  \return l'élement correspondant.
	 */
	inline double &operator()(int i) {
		return m_c[i];
	}

	/*!
	  *  \brief Renvoie x ou a (le premier élément du triplet).
	  *
	  *  \return x
	  */
	inline double x() const {return m_c[0];}
	inline double a() const {return m_c[0];}

	/*!
	  *  \brief Renvoie y ou b (le deuxième élément du triplet).
	  *
	  *  \return y
	  */
	inline double y() const {return m_c[1];}
	inline double b() const {return m_c[1];}

	/*!
	  *  \brief Renvoie z ou c (le dernier élément du triplet).
	  *
	  *  \return z
	  */
	inline double z() const {return m_c[2];}
	inline double c() const {return m_c[2];}



	/*!
	  *  \brief Set x ou a.
	  *
	  *  \param k : un double
	  */
	inline void x(double k) {m_c[0]=k;}
    inline void a(double k) {m_c[0]=k;}

    /*!
	  *  \brief Set y ou b.
	  *
	  *  \param k : un double
	  */
    inline void y(double k) {m_c[1]=k;}
    inline void b(double k) {m_c[1]=k;}
    /*!
	  *  \brief Set z ou c.
	  *
	  *  \param k : un double
	  */
    inline void z(double k) {m_c[2]=k;}
    inline void c(double k) {m_c[2]=k;}

    /*!
	  *  \brief Ajoute aux éléments existant du Vector3,
	  *  les éléments (x,y,z).
	  *
	  *  \param x : un double
	  *  \param y : un double
	  *  \param z : un double
	  *
	  */
	void add(double x,double y,double z);

	/*!
	  *  \brief Affiche les éléments du Vector3.
	  *
	  *
	  */
	void printV() const;

	/*!
	  *  \brief Destructeur.
	  *
	  *  Désalloue les éléments dynamiques.
	  *
	  */
	virtual ~Vector3();

protected:
	double m_c[3];

};

#endif
