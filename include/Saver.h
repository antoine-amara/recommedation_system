#ifndef SAVER_H
#define SAVER_H

#include <string>
#include <gsl/gsl_matrix.h>

#include "MovieRecommender.h"

/*!
 * \file Saver.h
 * \brief Permets de sauvegarder l'état de l'IA.
 * \author Antoine Amara, Jean-Fréderic Durand.
 * \version 0.2
 */

 /*! \class Saver
   * \brief Classe représentant une sauvegarde de l'IA.
   *
   *  La classe gère la sauvegarde d'un état de l'IA dans un fichier. Elle permet également de charger
   *  le contenu d'un fichier de sauvegarde.
   */

class Saver {

public:
  /*!
     *  \brief Constructeur par défaut.
     *
     *  Ce constructeur considérera que le nom du fichier de sauvegarde
     *  est mr.save.
     *
     */

  Saver();
  /*!
     *  \brief Constructeur
     *
     *  Ce constructeur prend un nom de fichier de sauvegarde. le nom du fichier sera donc filename.save.
     *
     *  \param filename : le nom du fichier de sauvegarde à charger ou à écrire.
     */
  Saver(std::string filename);

  /*!
     *  \brief Sauvegarde d'une IA.
     *
     *  Méthode permettant de sauvegarder l'état d'un objet MovieRecommender(de l'IA donc).
     *  Les éléments sauvegardés seront les matrices thêta et X, qui sont les matrices des paramètres
     *  permettant d'effectuer des prédictions(et donc de déduire des recommandations par la suite).
     *  Le taux d'apprentissage alpha sera également sauvegardé si il est disponible.(dans le cas d'une IA
     *  en cours d'entraînement). Le tout sera sauvegardé dans le fichier filename.save.
     *
     *  \param object : l'objet représentant l'IA a sauvegardé.
     */
  void save(MovieRecommender object);

  /*!
     *  \brief Chargement d'un état d'une IA.
     *
     *  Méthode permettant de charger un état d'un objet MovieRecommender(de l'IA donc)
     *  précédemment sauvegardé dans un fichier filename.save. Les éléments chargés seront
     *  les matrices de paramètres thêta et X permettant de faire des prédictions(et donc
     *  d'effectuer des recommandations), si il a été sauvegardé, le taux d'apprentissage alpha
     *  sera également chargé.
     *
     */
  void load();

  /*!
     *  \brief Récupérer la matrice thêta.
     *
     *  Getter permettant de récupérer la matrice de paramètres thêta(représentant les préférences utilisateur).
     *
     *  \return une gsl_matrix avec l'ensemble des données de préférence, par utilisateur.
     */
  gsl_matrix* getTheta();

  /*!
     *  \brief Récupérer la matrice X.
     *
     *  Getter permettant de récupérer la matrice de paramètres X(représentant la catégorisation des films).
     *
     *  \return une gsl_matrix avec des valeurs(double) représentant l'appartenance de chaque film aux différentes catégories.
     */
  gsl_matrix* getX();

  /*!
     *  \brief Récupérer le taux d'apprentissage.
     *
     *  Getter permettant de récupérer le taux d'apprentissage. Celui-ci est défini seulement si le saver
     *  a été utilisé durant un entraînement.
     *
     *  \return un double représentant le taux d'apprentissage.
     */
  double getAlpha();

  /*!
     *  \brief Destructeur
     *
     *  Permets de désallouer les éléments dynamiques, ici ce sera les gsl_matrix m_theta et m_X.
     */
  virtual ~Saver();

protected:
  string m_filename; /*!< Nom du fichier de sauvegarde, utilisé aussi bien pour l'écriture que la lecture */
  gsl_matrix* m_theta; /*!< Matrice de paramètres thêta, représente les préférences des utilisateurs */
  gsl_matrix* m_X; /*!< Matrice de paramètres X, représente la catégorisation des films */
  double m_alpha; /*!< Le taux d'apprentissage utilisé lors d'un entraînement de l'IA */
};

#endif
