#include "Vector3.h"

using namespace std;

/*********************************************************/
/* Main de test pour le Vector3                          */
/* Test de définir des tableaux de Vector3 dynamique     */
/* Exemple de fonctionnement de la classe Vector3        */
/*********************************************************/

int main(void){
  //
  Vector3 test[0] = Vector3();

  test[0].set(1,0,0);

  test[0].printV();

  test[11].set(2,2,2);

  test[11].printV();

  return 0;
}
