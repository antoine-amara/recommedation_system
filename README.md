Recommendation System{#mainpage}
=========

## PJI : système de recommandation d'items (Films)

> version 1.0

Dans le cas d'une recommandation de films :
* Les datasets: [grouplens](http://grouplens.org/datasets/movielens/)

outils utilisés (pré-requis):
* GNU GSL: [site officiel](http://www.gnu.org/software/gsl/)
* Doxygen: [site officiel](http://www.doxygen.org)

## Organisation du projet:
* src: contient les fichiers .cpp
* include: contient les fichiers .h
* build: contient les binaires et l'éxecutable
* doc: contient la documentation
* test: contient des main de test


## Instructions de compilation:
* compiler les sources du projet: make
* créer la documentation du projet: make doc
* nettoyer le projet: make mrproper

## Mini man:

> ./recommender_system [options] [arguments]

*options:*

> -T [dataset] [nbFilms] [nbUsers] [nbGenres] [alpha] [lambda] : lance un entrainement (MovieRecommender::train) depuis un fichier source.
* si aucun argument n'est fourni, lance un entrainement (MovieRecommender::train) avec les parmètre par défaut sur le dataset par défaut (u1).
* si l'argument dataset est fourni alors il est nécéssaire de fournir nbFlms, nbUsers et nbGenres.
* lambda et alpha sont par défaut réglés respectivement à 5/100 et 10^(-4).

> -S [dataset] [alpha] [lambda] : lance un entrainement (MovieRecommender::train) depuis une sauvegarde.
* si aucun argument n'est fourni, lance un Saver avec le dataset par défaut(u1).
* lambda et alpha sont par défaut réglés respectivement à 5/100 et 10^(-4).

> -V [datasets] [nbDataSets] [nbLignesSurUnJeu] : Lance une cross-Validation (Validator::startRMSE)
* si aucun argument n'est fourni, lance la cross-validation (Validator::startRMSE) sur les jeux de données par défaut (u1 à u5).
* si l'argument datasets est fourni alors il est nécéssaire de nbDataSets et nbLignesSurUnJeu.

> -R [dataset] [idUser] [nbRecommand] : lance une recommandation (MovieRecommender::recommend)
* si aucun argument n'est fourni, lance la recommandation pour l'utilisateur numéro 13 avec 5 films.
* pour les autres cas fournir les 3 arguments.
