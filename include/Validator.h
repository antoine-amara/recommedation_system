#include <iostream>
#include <vector>
#include <numeric>
#include <string>

#include "Vector3.h"
#include "MovieRecommender.h"
#include "Saver.h"
#include "DataParser.h"

class Validator {

public:
	/*!
	 *  \brief Constructeur par défaut.
	 *
	 */
	Validator(int N);

	/*!
	 *  \brief Constructeur prennant en paramètre un nom
	 *  de fichier et un nombre de set de tests.
	 *
	 *  \param filename : Un string correspondant au nom de fichier de base.
	 *  \param nbTestSets : Un int correspondant aux nombres de set de tests voulu.
	 *	\param N : le nombre d'entrées dans les datasets de test.
	 */
	Validator(std::string filename, int nbTestSets, int N);

	/*!
	 *  \brief Lance l'analyse du validateur et imprime un rapport.
	 *
	 *
	 */
	void start();

	void startRMSE();

	/*!
	 *  \brief Calcul l'erreur d'un dataset.
	 *  La fonction calcul l'erreur d'un dataset et l'ajoute au vector<int>
	 *  m_errors.
	 *
	 *  \param dataset : Un string correspondant au nom du dataset
	 *
	 */
	 void computeError(std::string dataset);

	 void computeRMSE(std::string dataset);

	 /*!
	 *  \brief Calcul l'erreur de l'ensemble des dataset.
	 *  La fonction somme l'ensemble des erreurs calculées dans
	 *  m_errors et renvoie la moyenne des erreurs.
	 *
	 *
	 *  \return un entier correspondant au résultat
	 */
	 double computeGlobalError();

	 /*!
	 *  \brief Affiche un rapport détaillé des opérations effectués lors d'un
	 *  computeGlobalError().
	 *
	 */
	 void printReport();

	 /*!
     *  \brief Destructeur
     *
     *  Permets de désallouer les éléments dynamiques.
     */
  	virtual ~Validator();

protected:
	std::string m_filename; /*!< Nom de base des datasets nescessaire à la validation */
  int m_nbTestSets; /*!< Nombre de fichiers test */
	int m_N; /*!< Nombre d'entrées dans les datasets de test */
  std::vector<double> m_errors; /*!< Le Vecteur des erreurs commise par le MovieRecommender */
};
