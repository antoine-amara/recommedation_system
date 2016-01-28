#ifndef MOVIERECOMMENDER_H
#define MOVIERECOMMENDER_H

#include <string>
#include <vector>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

#include "AiInterface.h"
#include "DataParser.h"

class Saver;

/*!
 * \file MovieRecommender.h
 * \brief Algorithme d'apprentissage permettant de recommander des films à un utilisateur.
 * \author Antoine Amara, Jean-Fréderic Durand.
 * \version 0.3
 */

 /*! \class MovieRecommender
   * \brief Classe représentant l'algorithme de recommandation de film.
   *
   *  La classe gère la représentation des données, l'apprentissage, la sauvegarde des résultats et bien sûr la recommandation.
   */

class MovieRecommender : public AiInterface {

public:
  /*!
     *  \brief Constructeur de base.
     *
     *  Ce constructeur prend le nombre de films et d'utilisateur à traité. Le nom du dataset sera ici celui
     *  par défaut, c'est-à-dire "u", on aura donc les fichiers suivants:
     *    - u.base
     *    - u.genre
     *    - u.item
     *
     *  \param nbMovies: le nombre total de films traité par l'algorithme.
     *  \param nbUsers: le nombre total d'utilisateurs traité par l'algorithme.
     */
  MovieRecommender(int nbMovies, int nbUsers);

  /*!
     *  \brief Constructeur avec un nom de fichier.
     *
     *  Ce constructeur prend un nom de fichier et le nombre de films et d'utilisateurs à traité.
     *  Ici, on aura donc les fichiers suivants:
     *    - dataset.base
     *    - dataset.genre
     *    - dataset.item
     *
     *  \param dataset: le nom du dataset à utiliser.
     *  \param nbMovies: le nombre total de films traité par l'algorithme.
     *  \param nbUsers: le nombre total d'utilisateurs traité par l'algorithme.
     */
  MovieRecommender(std::string dataset, int nbMovies, int nbUsers);

  /*!
     *  \brief Constructeur avec initialisation des matrices thêta et X.
     *
     *  Ce constructeur prend un nom de fichier et le nombre de films et d'utilisateurs à traité.
     *  Ici, on aura donc les fichiers suivants:
     *    - dataset.base
     *    - dataset.genre
     *    - dataset.item\n
     *  Enfin, les deux matrices de paramètres thêta(représentant les préférences utilisateur par genre) et
     *  X(représentant la catégorisation par genre de chaque film) sont données. Les 2 matrices doivent
     *  avoir la taille donnée par les variables nbMovies et nbUsers.
     *
     *  \param dataset: le nom du dataset à utiliser.
     *  \param nbMovies: le nombre total de films traité par l'algorithme.
     *  \param nbUsers: le nombre total d'utilisateurs traité par l'algorithme.
     *  \param theta: la matrice de paramètres thêta, représentant ici les préférences utilisateur pour chaque genre de film.
     *  \param X: la matrice de paramètres X, représentant l'appartenance de chaque film à un genre.
     */
  MovieRecommender(std::string dataset, int nbMovies, int nbUsers, gsl_matrix* theta, gsl_matrix* X);

  /*!
     *  \brief Constructeur avec initialisation des matrices thêta et X via un Saver.
     *
     *  Constructeur permettant l'initialisation de l'algorithme via un objet Saver qui charge les informations
     *  via deux fichiers(filename.theta pour la matrice Theta et filename.X pour X).
     *
     *  \param dataset: le nom du dataset à utiliser.
     *  \param saver: l'objet saver permettant de charger les matrices thêta et X.
     */
  MovieRecommender(std::string dataset, Saver saver);

  /*!
     *  \brief Permets d'effectuer l'apprentissage.
     *
     *  Méthode permettant d'effectuer l'apprentissage, c'est à dire d'affiner les paramètres thêta et X
     *  permettant de produire des prédictions qui vont servir pour effectuer les recommandations.
     *  On notera que l'entrainement se fait grâce à une décente de gradient. Le taux d'apprentissage alpha permet
     *  de déterminer la vitesse de la décente du gradient.
     *
     *  \param alpha : le taux d'apprentissage utilisé pour la décente de gradient.
     */
  void train(double alpha);

  /*!
     *  \brief Construire la matrice complète notes des films/utilisateurs.
     *
     *  Méthode permettant de prédire les notes de chaque film pour chaque utilisateur. Ceci a pour résultat
     *  de construire la matrice complète des notes des films par rapport aux utilisateurs. On utilisera donc
     *  cette matrice pour effectuer les recommandations aux utilisateurs. On notera que l'on se base sur
     *  les matrices de paramètres thêta et X pour effectuer les prédictions, donc il faut utiliser ce modèle
     *  pour faire des recommandations seulement si l'entrainement a été effectué.
     *
     */
  void predict();

  /*!
     *  \brief Recommander des films à un utilisateur.
     *
     *  Méthode permettant de trouver des films similaires à un film que l'utilisateur a apprécié.
     *
     *  \param user : l'id de l'utilisateur pour lequel ont fera la prédiction.
     *  \param nbMovies: le nombre de films a recommandé.
     *  \return un vector de string avec le titre des films recommandés.
     */
  std::vector<std::string> recommend(int user, int nbMovies);

  /*!
     *  \brief Calcul de la fonction de cout J(thêta).
     *
     *  Méthode permettant de calculer la fonction de coût, qui représente la performance de l'algorithme.
     *  C'est donc une erreur qui est calculée. Cette erreur doit être minimale pour assurer la performance des recommandations effectuée.
     *  L'entraînement est là pour minimiser cette erreur.
     *
     *  \return un double représentant l'erreur globale que commet l'algorithme sur ces prédictions.
     */
  double computeCost();

  /*!
     *  \brief Sauvegarde d'un état de l'objet.
     *
     *  Méthode permettant de sauvegarder l'état de l'objet, c'est-à-dire l'état des matrices thêta et X.
     *  Cette méthode utilise simplement un objet Saver pour faire ça.
     *
     *  \param file : le nom du fichier de sauvegarde.
     */
  void saveState(std::string file);

  /*!
     *  \brief Chargement d'un état de l'objet.
     *
     *  Méthode permettant de charger l'état de l'objet précédemment sauvegardé par un Saver.
     *  On va charger directement thêta et X dans les attributs respectifs de l'objet. Le chargement se
     *  fera via un objet Saver.
     *
     *  \param file : le nom du fichier de sauvegarde.
     */
  void loadState(std::string file);

  /*!
     *  \brief Affichage de l'état de l'objet.
     *
     *  Méthode permettant d'afficher les informations utiles sur l'état de l'objet, c'est-à-dire:
     *    - la matrice de paramètres thêta.
     *    - la matrice de paramètres X.
     *    - la fonction de cout J(thêta).
     *
     */
  void printState();

  /*!
     *  \brief Changer le dataset.
     *
     *  Setter permettant de charger un nouveau dataset pour l'entraînement.
     *
     *  \param set : le nom du dataset.
     */
  void setDatas(std::string set);

  /*!
     *  \brief Récupérer la matrice de paramètres thêta.
     *
     *  Getter permettant de récupérer la matrice de paramètre thêta qui correspond aux préférences des utilisateurs.
     *
     *  \return une gsl_matrix avec l'ensemble des données de préférence, par utilisateur.
     */
  gsl_matrix* getTheta();

  /*!
     *  \brief Récupérer la matrice de paramètres X.
     *
     *  Getter permettant de récupérer la matrice de paramètre thêta qui correspond aux catégorisations des films.
     *
     *  \return une gsl_matrix avec des valeurs(double) représentant l'appartenance de chaque film aux différentes catégories.
     */
  gsl_matrix* getX();

  /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe MovieRecommender.
     *
     *  Permets de désallouer les éléments dynamiques, ici ce sera les gsl_matrix m_theta, m_X et m_ratings.
     */
  virtual ~MovieRecommender();

protected:
  gsl_matrix* m_theta; /*!< Matrice de paramètres, elle représente les préférences des utilisateurs en fonction des genres de films. */
  gsl_matrix* m_X; /*!< Matrice de paramètres, elle représente la catégorie de chaque film. */
  gsl_matrix* m_ratings; /*!< Matrice contenant les predictions. On a donc la matrice complète des notes des films données par l'ensemble des utilisateurs. */
  DataParser m_parser; /*!< Objet DataParser contenant les informations du dataset, c'est-à-dire la matrice des notes données par les utilisateurs(incomplète), l'ensemble des genres de films présents dans le dataset ainsi que les titres de tous les films. */
};

#endif
