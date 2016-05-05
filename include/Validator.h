#include <iostream>
#include <vector>
#include <numeric>
#include <string>

#include "Vector3.h"
#include "MovieRecommender.h"
#include "Saver.h"
#include "DataParser.h"

/*!
 * \file Validator.h
 * \brief Classe permettant d'effectuer une cross-validation après un entraînement.
 * \author Antoine Amara, Jean-Fréderic Durand.
 * \version 1.0
 */

 /*! \class Validator
   * \brief Classe permettant de faire une cross-validation.
   *
   *  La classe permet de mettre en place de façon automatisée une cross-validation après un entraînement.
	 * Elle permet ainsi de valider un apprentissage soit par rapport au nombre d'erreurs de prédictions, soit par rapport à la fonction de coût.
	 * Elle fonctionne avec plusieurs jeux de données, il suffit de lui donner le nom du set de données et le nombre total de jeux et elle calcule l'erreur sur l'ensemble.
	 * par exemple si le jeu de données se nomme u et qu'il y a 5 jeux en tout, elle calculera l'erreur sur les fichiers u1.test, u2.test, u3.test, u4.test et u5.test.
   */

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
	 *  \brief Lance l'analyse du validateur.
	 *
	 *	Demarre l'analyse et imprime un rapport sur la sortie standard. L'analyse se fait ici par rappor au nombre prediction fausse.
	 *
	 */
	void start();

	/*!
	 *  \brief Lance l'analyse du validateur.
	 *
	 * Demarre l'analyse et imprime un rapport sur la sortie standard. L'analyse se fait ici par rappor à la fonction de coût (RMSE).
	 *
	 */
	void startRMSE();

	/*!
	 *  \brief Calcul l'erreur d'un dataset.
	 *  La fonction calcule les erreurs de prédictions d'un jeu de données et sauvegarde la valeur dans l'attribut m_errors.
	 *
	 *  \param dataset : Un string correspondant au nom du dataset
	 *
	 */
	 void computeError(std::string dataset);

	 /*!
 	 *  \brief Calcul l'erreur d'un dataset.
 	 *  La fonction calcule les erreurs de prédictions d'un jeu de données en calculant la fonction de coût (RMSE) et sauvegarde la valeur dans l'attribut m_errors.
 	 *
 	 *  \param dataset : Un string correspondant au nom du dataset
 	 *
 	 */
	 void computeRMSE(std::string dataset);

	 /*!
	 *  \brief Calcul l'erreur de l'ensemble des dataset.
	 *  La fonction somme l'ensemble des erreurs calculées dans
	 *  m_errors et renvoie la moyenne des erreurs.
	 *
	 *
	 *  \return un réel correspondant au résultat
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
