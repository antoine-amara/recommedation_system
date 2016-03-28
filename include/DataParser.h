#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <gsl/gsl_matrix.h>

#include "ParserInterface.h"
#include "Vector3.h"

/*!
 * \file DataParser.h
 * \brief Le parser à utilisé pour le système de recommandation de films.
 * \author Antoine Amara, Jean-Fréderic Durand.
 * \version 0.3
 */

/*! \class DataParser
   * \brief Classe représentant le parser de données pour le système de recommandation de films.
   *
   *  La classe gère la lecture des différents fichiers du dataset pour récupérer les différentes données utiles au
   *  bon fonctionnement de l'algorithme.
   */

class DataParser : public ParserInterface {

public:

  DataParser();
  /*!
     *  \brief Constructeur par défaut.
     *
     *
     *  Ce constructeur considérera que le nom du fichier du dataset sera u.
     *  On considérera donc les fichiers suivants:
     *    - u.data
     *    - u.genre
     *    - u.item
     *
     *  \param nbMovies : nombre total de films disponible.
     *  \param nbUsers : nombre total d'utilisateur.
     */
  DataParser(int nbMovies, int nbUsers);

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
  DataParser(std::string filename, int nbMovies, int nbUsers);

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
     *  Ces informations sont stockées dans le fichier filename.data et sont organisées de la manière suivante:\n
     *    utilsateur id   film id    note    timestamp\n
     *  On notera que le séparateur est une tabulation.
     *
     */
  void parseDatas();

  /*!
     *  \brief Récupération des genres de films.
     *
     *  Méthode permettant de récupérer les informations de classification. Ici les films sont catégorisés par leur genre.
     *  Ces informations sont stockées dans le fichier filename.genre et sont organisés de la manière suivante:\n
     *    genre|nombre de film de ce genre\n
     *  On notera que le séparateur est ici un pipe, que les notes vont de 1 à 5, l'utilisateur n'a pas noté tous les films,
     *  dans ce cas la case contient un 0.
     *
     */
  void parseGenres();

  /*!
     *  \brief Récupération des informations sur les films.
     *
     *  Méthode permettant de récupérer l'ensemble des informations relatives aux films.
     *  Ces informations sont stockées dans le fichier filename.item et sont organisés de la manière suivante:\n
     *    film id|titre|date de sortie|date de sortie en video|IMDb url|genre\n
     *  On notera que le séparateur est ici le pipe et que le genre est représenté par une suite de booléens.
     *
     */
  void parseMovies();

  /*!
     *  \brief Récupération des données d'un set de test.
     *
     *  Méthode permettant de récupérer l'ensemble des informations relatives à un set de test, c'est à dire les notes données par des utilisateurs à des films. Ces informations nous servent à vérifier que l'apprentissage est correct.
     *  Ces informations sont stockées dans le fichier filename.test et sont organisés de la manière suivante:\n
     *    utilsateur id   film id    note    timestamp\n
     *  On notera que le séparateur est une tabulation.
     *
     */
  void parseTest(Vector3* d, int N);

  /*!
     *  \brief Récupérer la matrice des notes précédemment construite par parseDatas.
     *
     *  Getter permettant de récupérer la matrice des notes utilisateur.
     *
     *  \return une gsl_matrix avec les notes des films par rapport aux utilisateurs, c'est-à-dire que
     *          chaque ligne est un film et chaque colonne un utilisateur.
     */
  gsl_matrix* getDatas();

  /*!
     *  \brief Récupérer le paramètre N du dataset.
     *
     *  Getter permettant de récupérer le paramètre N du dataset qui correspond au nombre de données présente dans celui-ci.
     *
     *  \return un entier représentant le nombre de ligne que l'on a compté.
     */
  int getN();

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
  int m_nbMovies; /*!< Le nombre total de films disponible */
  int m_nbUsers; /*!< Le nombre total d'utilisateur */
  int m_N; /*!< Le nomre de données présente dans le dataset */
  gsl_matrix *m_datas; /*!< La matrice contenant les notes des films données par les utilisateurs */
  std::vector<std::string> m_genres; /*!< Un tableau contenant les noms des genres des films */
  std::vector<std::string> m_movies; /*!< Un tableau contenant les titres des films */

private:
  /*!
     *  \brief Permets de découper une chaîne de caractères.
     *
     *  Méthode permettant de découper une chaîne de caractères suivant un séparateur.
     *
     *  \param str: la chaîne de caractères à splitté.
     *  \param separator: le séparateur choisit pour splitter.
     *
     *  \return un vector de string contenant les éléments splittés de la chaîne.
     */
  std::vector<std::string> split(std::string str, char separator);
};

#endif
