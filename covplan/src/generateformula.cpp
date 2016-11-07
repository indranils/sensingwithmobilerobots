#include <iostream>
#include <fstream>
#include <algorithm>
#include "../utils/primitive.h"
#include "../utils/readinputs.h"
#include "definepropositions.h"


void generateFormula(ofstream &ofp, workspace_t workspace, pos_vec_t obstacles)
{
  unsigned int count, count1, count2, count3;
  bool flag;

  count = 0;

  for (count1 = 0; count1 <= workspace.length_x; count1++)
  {
    for (count2 = 0; count2 <= workspace.length_y; count2++)
    {
      flag = false;
      for (count3 = 0 ; count3 < obstacles.size(); count3++)
      {
        if (obstacles[count3].x == count1 && obstacles[count3].y == count2)
        {
          flag = true;
          break;
        }
      }

      if (flag == false)
      {
        if (count > 0)
          ofp << " /\\ " << endl;
        ofp << "(<> (cover_" << count1 << "_" << count2 << " /\\ <> back))";
        count++;
      }
    }
  }
}

/*
void generateFormula(ofstream &ofp, workspace_t workspace, pos_vec_t obstacles)
{
  unsigned int count, count1, count2, count3;
  bool flag;
  
  count = 0;
  ofp << "(<> (";

  for (count1 = 0; count1 <= workspace.length_x; count1++)
  {
    for (count2 = 0; count2 <= workspace.length_y; count2++)
    {
      flag = false;
      for (count3 = 0 ; count3 < obstacles.size(); count3++)
      {
        if (obstacles[count3].x == count1 && obstacles[count3].y == count2)
        {
          flag = true;
          break;
        }
      }
        
      if (flag == false)
      {
        if (count > 0)
          ofp << " /\\ ";
        ofp << "(<> cover_" << count1 << "_" << count2 << ")";
        count++;
      }
    }
  }
  ofp << ") /\\ <>back)" << endl;
}
*/
