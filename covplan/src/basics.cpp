#include <iostream>
#include "basics.h"


bool isObstacle (pos_vec_t obstacles, unsigned int x, unsigned int y)
{
  bool flag;
  int count;

  flag = false;
  for (count = 0 ; count < obstacles.size(); count++)
  {
    if (obstacles[count].x == x && obstacles[count].y == y)
    {
      flag = true;
      break;
    }
  }
  return flag;
}
