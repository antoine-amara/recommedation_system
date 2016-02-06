#ifndef AIINTERFACE_H
#define AIINTERFACE_H

/*!
 * \file AiInterface.h
 * \brief Base de tout algorithme de machine learning.
 * \author Antoine Amara, Jean-Fréderic Durand.
 * \version 0.3
 */

 /*! \class AiInterface
   * \brief Interface représentant un algorithme de machine learning basique.
   *
   *  L'interface contient les méthodes basiques pour tout algorithme de machine learning.
   */

class AiInterface {

public:
  /*!
     *  \brief Permets l'entraînement de l'algorithme.
     *
     *  Méthode permettant d'effectuer l'apprentissage, c'est-à-dire d'affiner les paramètres de l'algorithme pour résoudre le problème voulu.
     *
     *  \param alpha: le taux d'apprentissage, il définit la vitesse de l'entrainement.
     */
  virtual void train(double alpha, double lambda) = 0;

  /*!
     *  \brief Permets d'effectuer une à plusieurs prédictions.
     *
     *  Méthode permettant d'évaluer une instance du problème voulu, si l'algorithme est entrainé, il doit pouvoir approcher la réponse du problème(d'une valeur extrêmement proche).
     *
     */
  virtual void predict() = 0;

  /*!
     *  \brief Calcul de la fonction de coût.
     *
     *  Méthode permettant de calculer la fonction de coût qui représente la performance de l'algorithme. Cette fonction de cout est donc l'erreur commise durant une prédiction.
     *
     *  \return l'erreur globale commise par l'algorithme sur une prédiction.
     */
  virtual double computeCost(double lambda) = 0;
};

#endif
