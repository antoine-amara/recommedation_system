#ifndef PARSERINTERFACE_H
#define PARSERINTERFACE_H

/*! \class ParserInterface
   * \brief Interface permettant d'avoir la base d'un parser.
   *
   *  Cette classe contient les méthodes de base de tout parser.
   */

class ParserInterface {

public:
  /*!
     *  \brief Méthode permettant de parser un fichier.
     *
     *  On récupère ici tous les éléments utiles du fichier à parser.
     */
  virtual void parse() = 0;
};

#endif
