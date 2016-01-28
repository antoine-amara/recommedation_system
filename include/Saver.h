#ifndef SAVER_H
#define SAVER_H

#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <assert.h>
#include <gsl/gsl_matrix.h>

#include "MovieRecommender.h"

/*!
 * \file Saver.h
 * \brief Permets de sauvegarder l'état de l'IA.
 * \author Antoine Amara, Jean-Fréderic Durand.
 * \version 0.3
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
     *  est mr. La sauvegarde/chargement sera effectuer dans les fichiers mr.theta et mr.X.
     *
     */
  Saver();

  /*!
     *  \brief Constructeur
     *
     *  Ce constructeur prend un nom de fichier de sauvegarde. le nom des fichiers de sauvegarde seront filename.theta et filename.X.
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
     *  Theta sera sauvegardé dans le fichier filename.theta et X dans le fichier filename.X.
     *
     *  \param object : l'objet représentant l'IA a sauvegardé.
     */
  void save(MovieRecommender object);

  /*!
     *  \brief Chargement d'un état d'une IA.
     *
     *  Méthode permettant de charger un état d'un objet MovieRecommender(de l'IA donc)
     *  précédemment sauvegardé dans 2 fichiers: filename.theta et filename.X. Les éléments chargés seront
     *  les matrices de paramètres thêta et X permettant de faire des prédictions(et donc
     *  d'effectuer des recommandations).
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
     *  \brief Récupère le nombre de films
     *
     *  Getter permettant de récupérer le nombre entier représentant le nombre de ligne de la matrice Theta.
     *
     *  \return un entier.
     */
  int getNbMovies();

  /*!
     *  \brief Récupère le nombre d'utilisateurs.
     *
     *  Getter permettant de récupérer le nombre entier représentant le nombre de ligne de la matrice X.
     *
     *  \return un entier.
     */
  int getNbUsers();

  /*!
     *  \brief Destructeur
     *
     *  Permets de désallouer les éléments dynamiques, ici ce sera les gsl_matrix m_theta et m_X.
     */
  virtual ~Saver();

protected:
  std::string m_filename; /*!< Nom du fichier de sauvegarde, utilisé aussi bien pour l'écriture que la lecture */
  gsl_matrix* m_theta; /*!< Matrice de paramètres thêta, représente les préférences des utilisateurs */
  gsl_matrix* m_X; /*!< Matrice de paramètres X, représente la catégorisation des films */
  int m_nbMovies; /*!< Nombre de films, représente le nombre de ligne de theta (sauvegardé en première ligne du fichier .theta)*/
  int m_nbUsers; /*!< Nombre d'utilisateur, représente le nombre de ligne de X (sauvegardé en première ligne du fichier .X)*/
};

#endif
