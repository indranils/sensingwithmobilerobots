#include <iostream>
#include <fstream>
#include "primitive.h"
#include "readinputs.h"
#include "definepropositions.h"


void declarePropositions(ofstream &ofp, dimension_t dimension, pos_vec_t obstacles, int number_of_robots, int number_of_points)
{
  unsigned int count, count1, count2;

  for (count = 0; count < number_of_points; count++)
  {
    for (count1 = 0; count1 <= dimension.length_x; count1++)
    { 
      for (count2 = 0; count2 <= dimension.length_y; count2++)
      {
        if (isObstacle(obstacles, count1, count2) == false)
          ofp << "(declare-const cover_" << count1 << "_" << count2 << "_" << count + 1 << " Bool)" << endl;
      }
    }
  }

  for (count1 = 0; count1 <= dimension.length_x; count1++)
  {
    for (count2 = 0; count2 <= dimension.length_y; count2++)
    {
      if (isObstacle(obstacles, count1, count2) == false)
        ofp << "(declare-const cover_" << count1 << "_" << count2 << " Bool)" << endl;
    }
  }
  ofp << "(declare-const back  Bool)" << endl;
  ofp << endl;
}


void declarePenaltyVariables(ofstream &ofp, dimension_t dimension, pos_vec_t obstacles)
{
  unsigned int count1, count2;

  for (count1 = 0; count1 <= dimension.length_x; count1++)
  {
    for (count2 = 0; count2 <= dimension.length_y; count2++)
    {
      if (isObstacle(obstacles, count1, count2) == false)
      {
        ofp << "(declare-const penalty_" << count1 << "_" << count2 << " Real)" << endl;
      }
    }
  }
  ofp << endl;
}


void definePropositions(ofstream &ofp, dimension_t dimension, pos_vec_t obstacles, int number_of_robots, int number_of_points)
{
  int count1, count2;
  unsigned int count, count4;
  int x, y;

  for (count = 0; count < number_of_points; count++)
  {
    for (count1 = 0; count1 <= dimension.length_x; count1++)
    {
      for (count2 = 0; count2 <= dimension.length_y; count2++)
      {
        if (isObstacle(obstacles, count1, count2) == false)
        {
          ofp << "(assert (=> (= cover_" << count1 << "_" << count2 << "_" << count + 1 << " true)";
          ofp << " (or "<< endl;
          for (count4 = 0; count4 < number_of_robots; count4++)
          {
            x = count1; y = count2;
            if (x >= 0 && y >= 0 && x <= dimension.length_x && y <= dimension.length_y) 
            {
              ofp << "  (and (= x_" << count4 + 1 << "_" << count + 1 << " " << x << ")";
              ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " " << y << "))" << endl;
            }
	    x = count1 + 1; y = count2;
            if (x >= 0 && y >= 0 && x <= dimension.length_x && y <= dimension.length_y)
            {
              ofp << "  (and (= x_" << count4 + 1 << "_" << count + 1 << " " << x << ")";
              ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " " << y << "))" << endl;
            }
            x = count1 - 1; y = count2;
            if (x >= 0 && y >= 0 && x <= dimension.length_x && y <= dimension.length_y)
            {
              ofp << "  (and (= x_" << count4 + 1 << "_" << count + 1 << " " << x << ")";
              ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " " << y << "))" << endl;
            }
            x = count1; y = count2 + 1;
            if (x >= 0 && y >= 0 && x <= dimension.length_x && y <= dimension.length_y)
            {
              ofp << "  (and (= x_" << count4 + 1 << "_" << count + 1 << " " << x << ")";
              ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " " << y << "))" << endl;
            }
            x = count1; y = count2 - 1;
            if (x >= 0 && y >= 0 && x <= dimension.length_x && y <= dimension.length_y)
            {
              ofp << "  (and (= x_" << count4 + 1 << "_" << count + 1 << " " << x << ")";
              ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " " << y << "))" << endl;
            }
            x = count1 + 1; y = count2 + 1;
            if (x >= 0 && y >= 0 && x <= dimension.length_x && y <= dimension.length_y)
            {
              ofp << "  (and (= x_" << count4 + 1 << "_" << count + 1 << " " << x << ")";
              ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " " << y << "))" << endl;
            }
            x = count1 + 1; y = count2 - 1;
            if (x >= 0 && y >= 0 && x <= dimension.length_x && y <= dimension.length_y)
            {
              ofp << "  (and (= x_" << count4 + 1 << "_" << count + 1 << " " << x << ")";
              ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " " << y << "))" << endl;
            }
            x = count1 + 1; y = count2 + 1;
            if (x >= 0 && y >= 0 && x <= dimension.length_x && y <= dimension.length_y)
            {
              ofp << "  (and (= x_" << count4 + 1 << "_" << count + 1 << " " << x << ")";
              ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " " << y << "))" << endl;
            }
            x = count1 - 1; y = count2 + 1;
            if (x >= 0 && y >= 0 && x <= dimension.length_x && y <= dimension.length_y)
            {
              ofp << "  (and (= x_" << count4 + 1 << "_" << count + 1 << " " << x << ")";
              ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " " << y << "))" << endl;
            }
          }
          ofp << ")))" << endl;
        }
      }
    }
  }
  ofp << endl;

  /* for (count = 0; count < workspace.number_of_points; count++)
  {
    ofp << "(assert (=> (= back_" << count + 1 << " true)";
    ofp << " (and " << endl;
    for (count4 = 0; count4 < workspace.number_of_robots; count4++)
    {
      ofp << " (or "<< endl;
      ofp << "(and ";
      ofp << "(= x_" << count4 + 1 << "_" << count + 1 << " x_" << count4 + 1 << "_1)";
      ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " y_" << count4 + 1 << "_1)";
      ofp << ")" << endl;
      ofp << "(and ";
      ofp << "(= x_" << count4 + 1 << "_" << count + 1 << " (+ x_" << count4 + 1 << "_1 1))";
      ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " y_" << count4 + 1 << "_1)";
      ofp << ")" << endl;
      ofp << "(and ";
      ofp << "(= x_" << count4 + 1 << "_" << count + 1 << " (- x_" << count4 + 1 << "_1 1))";
      ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " y_" << count4 + 1 << "_1)";
      ofp << ")" << endl;
      ofp << "(and ";
      ofp << "(= x_" << count4 + 1 << "_" << count + 1 << " x_" << count4 + 1 << "_1)";
      ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " (+ y_" << count4 + 1 << "_1 1))";
      ofp << ")" << endl;
      ofp << "(and ";
      ofp << "(= x_" << count4 + 1 << "_" << count + 1 << " x_" << count4 + 1 << "_1)";
      ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " (- y_" << count4 + 1 << "_1 1))";
      ofp << ")" << endl;
      ofp << "(and ";
      ofp << "(= x_" << count4 + 1 << "_" << count + 1 << " (+ x_" << count4 + 1 << "_1 1))";
      ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " (+ y_" << count4 + 1 << "_1 1))";
      ofp << ")" << endl;
      ofp << "(and ";
      ofp << "(= x_" << count4 + 1 << "_" << count + 1 << " (+ x_" << count4 + 1 << "_1 1))";
      ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " (- y_" << count4 + 1 << "_1 1))";
      ofp << ")" << endl;
      ofp << "(and ";
      ofp << "(= x_" << count4 + 1 << "_" << count + 1 << " (- x_" << count4 + 1 << "_1 1))";
      ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " (+ y_" << count4 + 1 << "_1 1))";
      ofp << ")" << endl;
      ofp << "(and ";
      ofp << "(= x_" << count4 + 1 << "_" << count + 1 << " (- x_" << count4 + 1 << "_1 1))";
      ofp << "(= y_" << count4 + 1 << "_" << count + 1 << " (- y_" << count4 + 1 << "_1 1))";
      ofp << "))" << endl;
    }
    ofp << ")))" << endl;
  } */
} 
