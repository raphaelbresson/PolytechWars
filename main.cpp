#include "ApplicationControl.h"

int main()
{
  ApplicationControl app(800,600);
  if(!app.init())
  {
    fprintf(stderr,"erreur d'Initialisation de l'application\n");
    return -1;
  }
  if(!app.execute())
  {
    fprintf(stderr,"Erreur lors de l'exécution\n");
    return -1;
  }
  return 0;
}
