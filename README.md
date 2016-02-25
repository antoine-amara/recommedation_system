# recommendation_system

__ pji système de recommandation de film, musique ou autre. __

Le dataset utilisé est u1.

Les datasets: [grouplens](http://grouplens.org/datasets/movielens/)

outils utilisés:
* GNU GSL: [site officiel](http://www.gnu.org/software/gsl/)
* Doxygen: [site officiel](http://www.doxygen.org)

## organisation du projet:
* src: contient les fichiers .cpp
* include: contient les fichiers .h
* build: contient les binaires et l'éxecutable
* doc: contient la documentation
* test: contient des main de test

## instructions de compilation:
* compiler les sources du projet: make
* créer la documentation du projet: make doc
* nettoyer le projet: make mrproper

## Debug report:
* fonction predict ok
* fonction computeError ok
* fonction computeCost ok mais pas sur a 100%
* train ok mais pas sur a 100% et algo evolue permettant de modifier alpha au cour du temps
* initParams segfault array out of bounds (je ne sais pas pourquoi les boucles sont pourtant simple !!!)
