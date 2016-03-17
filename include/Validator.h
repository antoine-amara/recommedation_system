#include <iostream>
#include <vector>

#include "Vector3.h"
#include "MovieRecommender.h"

class Validator {
	
public:
	/*!
	 *  \brief Constructeur par défaut.
	 *
	 */
	Validator();

	/*!
	 *  \brief Constructeur prennant en paramètre un nom 
	 *  de fichier et un nombre de set de tests.
	 *
	 *  \param filename : Un string correspondant au nom de fichier de base.
	 *  \param nbTestSets : Un int correspondant aux nombres de set de tests voulu.
	 */
	Validator();	


protected:
  int m_nbTestSets;
  /*!< Nombre de fichiers test */
  MovieRecommender m_movieRecommender;
  /*!< L'objet MovieReccommender permettant de faire les prédictions */
  std::vector<int> m_errors;
  /*!< Le Vecteur des erreurs commise par le MovieRecommender */
};