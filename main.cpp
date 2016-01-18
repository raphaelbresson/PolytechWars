#include "ApplicationControl.h"

int main()
{
  ApplicationControl app(800,600);
  if(!app.init())
    return -1;
  if(!app.execute())
    return -1;
  return 0;
}
