Entrainement 2
===================


Deuxième entraînement sur le jeux de données contenant 100 000 notes. Il y a 1643 films et 943 utilisateurs. Pour permettre une cross-validation les jeux de données sont séparer en 5 sets. Pour chaque set nous avons un set d'apprentissage avec 80% des données et un set de test avec les 20% restant.

----------


Configuration système
-------------
Les configurations système sont les suivante:

* Ubuntu 14.04 LTS
* 1800 Mo de mémoire RAM
* CPU single core


> **Note:**

> L'environement d'éxecution est une machine virtuelle

Configuration de l'IA
-------------

Les paramètres de l'algorithme sont les suivants pour l'ensemble des 5 entraînements:

* alpha = 0.001
* lambda = 1/100
* seuil du taux d'erreur: 0.1

> **Note:**

> Le seuil du taux d'erreur est la condition d'arret de la decente de gradient, dès que le taux d'erreur passe en dessous on s'arrete.

Rapport
-------------

### U1

* erreur en fin d'apprentissage: 0.0952622
* temps d'éxécution: 27.159s
* consomation mémoire: 50Mo (maximum)

### U2

* erreur en fin d'apprentissage: 0.0661727
* temps d'éxécution: 18.938s
* consomation mémoire: 50 Mo (maximum)

### U3

* erreur en fin d'apprentissage: 0.0970682
* temps d'éxécution: 12.189s
* consomation mémoire: 50 Mo (maximum)

### U4

* erreur en fin d'apprentissage: 0.0653083
* temps d'éxécution: 17.727s
* consomation mémoire: 50 Mo (maximum)

### U5

* erreur en fin d'apprentissage: 0.0935517
* temps d'éxécution: 14.901s
* consomation mémoire: 50 Mo (maximum)

Cross Validation
-------------

### U1
* taux d'erreur: 60%

### U2
* taux d'erreur: 59%

### U3
* taux d'erreur: 60%

### U4
* taux d'erreur: 59%

### U5
* taux d'erreur: 60%

Le taux d'erreur globale pour cette phase de test est donc de 59%, c'est médiocre.
