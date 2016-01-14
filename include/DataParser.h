#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <gsl/gsl_matrix.h>

#include "ParserInterface.h"

/*!
 * \file DataParser.h
 * \brief Le parser à utilisé pour le système de recommandation de films.
 * \author Antoine Amara, Jean-Fréderic Durand.
 * \version 0.1
 */

/*! \class DataParser
   * \brief Classe représentant le parser de données pour le système de recommandation de films.
   *
   *  La classe gère la lecture des différents fichiers du dataset pour récupérer les différentes données utiles au
   *  bon fonctionnement de l'algorithme.
   */

class DataParser : public ParserInterface {

public:
  /*!
     *  \brief Constructeur par défaut.
     *
     *  Constructeur par défaut de la classe DataParser.
     *
     *  Ce constructeur considérera que le nom du fichier du dataset sera u.
     *  On considérera donc les fichiers suivants:
     *    - u.data
     *    - u.genre
     *    - u.item
     */
  DataParser();

  /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe DataParser.
     *
     * Ce constructeur se base sur le nom passé en paramètre pour ouvrir les différents fichiers du dataset.
     * Ils seront donc les suivants:
     *    - filename.data
     *    - filename.genre
     *    - filename.item
     *
     *  \param filename : le nom du dataset.
     */
  DataParser(std::string filename);

  /*!
     *  \brief Récupération des données des fichiers.
     *
     *  Méthode permettant de récupérer et de stocker les informations utiles de l'ensemble des fichiers du dataset.
     *
     */
  void parse();

  /*!
     *  \brief Récupération des notes données par les utilisateurs.
     *
     *  Méthode permettant de récupérer les notes données aux différents films par les utilisateurs.
     *  Ces informations sont stockées dans le fichier filename.data et sont organisées de la manière suivante:
     *    film id   utilisateur id    note    timestamp
     *  On notera que le séparateur est une tabulation.
     *
     */
  void parseDatas();

  /*!
     *  \brief Récupération des genres de films.
     *
     *  Méthode permettant de récupérer les informations de classification. Ici les films sont catégorisés par leur genre.
     *  Ces informations sont stockées dans le fichier filename.genre et sont organisés de la manière suivante:
     *    genre|nombre de film de ce genre
     *  On notera que le séparateur est ici un pipe, que les notes vont de 1 à 5, l'utilisateur n'a pas noté tous les films,
     *  dans ce cas la case contient un -1.
     *
     */
  void parseGenres();

  /*!
     *  \brief Récupération des informations sur les films.
     *
     *  Méthode permettant de récupérer l'ensemble des informations relatives aux films.
     *  Ces informations sont stockées dans le fichier filename.item et sont organisés de la manière suivante:
     *    film id|titre/date de sortie|date de sortie en video|IMDb url|genre
     *  On notera que le séparateur est ici le pipe et que le genre est représenté par une suite de booléens.
     *
     */
  void parseMovies();

  /*!
     *  \brief Récupérer la matrice des notes précédemment construite par parseDatas.
     *
     *  Getter permettant de récupérer la matrice des notes utilisateur.
     *
     *  \return une gsl_matrix avec les notes des films par rapport aux utilisateurs, c'est-à-dire que
     *          chaque ligne est un film et chaque colonne un utilisateur.
     */
  gsl_matrix getDatas();

  /*!
     *  \brief Récupérer un tableau avec l'ensemble des genres précédemment construit par parseGenres.
     *
     *  Getter permettant de récupérer un tableau de string contenant l'ensemble des genres de films.
     *
     *  \return un vector de string contenant les noms des genres.
     */
  std::vector<std::string> getGenres();

  /*!
     *  \brief Récupérer un tableau avec les titres des films précédemment construit par parseMovies.
     *
     *  Getter permettant de récupérer un tableau de string contenant les titres des films. On notera que l'indice i du
     *  tableau correspond à l'id de chaque film.
     *
     *  \return un vector de string contenant les noms des films.
     */
  std::vector<std::string> getMovies();

  /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe DataParser.
     *
     *  Permets de désallouer les éléments dynamiques, ici ce sera la gsl_matrix m_datas.
     */
  virtual ~DataParser();

protected:
  std::string m_filename; /*!< Le nom du dataset */
  gsl_matrix m_datas; /*!< La matrice contenant les notes des films données par les utilisateurs */
  std::vector<std::string> m_genres; /*!< Un tableau contenant les noms des genres des films */
  std::vector<std::string> m_movies; /*!< Un tableau contenant les titres des films */
};

#endif
