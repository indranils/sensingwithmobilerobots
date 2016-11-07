#include <iostream>
#include <fstream>
#include "primitive.h"
#include "readinputs.h"
#include "definepropositions.h"
#include "generatecoverageconstraints.h"


void writeCoverageConstraints(ofstream &ofp, dimension_t dimension, pos_vec_t obstacles, int number_of_robots, int number_of_points)
{
  int count1, count2;
  unsigned int count, count4;

  for (count1 = 0; count1 <= dimension.length_x; count1++)
  {
    for (count2 = 0; count2 <= dimension.length_y; count2++)
    {
      if (isObstacle(obstacles, count1, count2) == false)
      {
        ofp << "(assert (=> (= cover_" << count1 << "_" << count2 << " true)";
        ofp << " (or " << endl;
        for (count = 0; count < number_of_points; count++)
        {
          ofp << "(= cover_" << count1 << "_" << count2 << "_" << count + 1 << " true)" << endl;
        }
        ofp << ")))" << endl;
      }
    }
  }

  ofp << endl;
  ofp << "(assert (=> (= back true)";
  ofp << " (and " << endl;
  for (count4 = 0; count4 < number_of_robots; count4++)
  {
    ofp << " (or "<< endl;
    ofp << "(and ";
    ofp << "(= x_" << count4 + 1 << "_" << number_of_points << " x_" << count4 + 1 << "_1)";
    ofp << "(= y_" << count4 + 1 << "_" << number_of_points << " y_" << count4 + 1 << "_1)";
    ofp << ")" << endl;
    ofp << "(and ";
    ofp << "(= x_" << count4 + 1 << "_" << number_of_points << " (+ x_" << count4 + 1 << "_1 1))";
    ofp << "(= y_" << count4 + 1 << "_" << number_of_points << " y_" << count4 + 1 << "_1)";
    ofp << ")" << endl;
    ofp << "(and ";
    ofp << "(= x_" << count4 + 1 << "_" << number_of_points << " (- x_" << count4 + 1 << "_1 1))";
    ofp << "(= y_" << count4 + 1 << "_" << number_of_points << " y_" << count4 + 1 << "_1)";
    ofp << ")" << endl;
    ofp << "(and ";
    ofp << "(= x_" << count4 + 1 << "_" << number_of_points << " x_" << count4 + 1 << "_1)";
    ofp << "(= y_" << count4 + 1 << "_" << number_of_points << " (+ y_" << count4 + 1 << "_1 1))";
    ofp << ")" << endl;
    ofp << "(and ";
    ofp << "(= x_" << count4 + 1 << "_" << number_of_points << " x_" << count4 + 1 << "_1)";
    ofp << "(= y_" << count4 + 1 << "_" << number_of_points << " (- y_" << count4 + 1 << "_1 1))";
    ofp << ")" << endl;
    ofp << "(and ";
    ofp << "(= x_" << count4 + 1 << "_" << number_of_points << " (+ x_" << count4 + 1 << "_1 1))";
    ofp << "(= y_" << count4 + 1 << "_" << number_of_points << " (+ y_" << count4 + 1 << "_1 1))";
    ofp << ")" << endl;
    ofp << "(and ";
    ofp << "(= x_" << count4 + 1 << "_" << number_of_points << " (+ x_" << count4 + 1 << "_1 1))";
    ofp << "(= y_" << count4 + 1 << "_" << number_of_points << " (- y_" << count4 + 1 << "_1 1))";
    ofp << ")" << endl;
    ofp << "(and ";
    ofp << "(= x_" << count4 + 1 << "_" << number_of_points << " (- x_" << count4 + 1 << "_1 1))";
    ofp << "(= y_" << count4 + 1 << "_" << number_of_points << " (+ y_" << count4 + 1 << "_1 1))";
    ofp << ")" << endl;
    ofp << "(and ";
    ofp << "(= x_" << count4 + 1 << "_" << number_of_points << " (- x_" << count4 + 1 << "_1 1))";
    ofp << "(= y_" << count4 + 1 << "_" << number_of_points << " (- y_" << count4 + 1 << "_1 1))";
    ofp << "))" << endl;
  }
  ofp << ")))" << endl;

  // For Complete Coverage
  ofp << endl;
  ofp << "(assert (and " << endl; 
  for (count1 = 0; count1 <= dimension.length_x; count1++)
  {
    for (count2 = 0; count2 <= dimension.length_y; count2++)
    {
      if (isObstacle(obstacles, count1, count2) == false)
      {
          ofp << "  (= cover_" << count1 << "_" << count2 << " true)" << endl;
      }
    }
  }
  ofp << "  (= back true)" << endl;
  ofp << "))" << endl << endl;

  /*
  // For Maximal Coverage
  ofp << endl;
  for (count1 = 0; count1 <= dimension.length_x; count1++)
  {
    for (count2 = 0; count2 <= dimension.length_y; count2++)
    {
      if (isObstacle(obstacles, count1, count2) == false)
      {
          ofp << "(assert (=>  (= cover_" << count1 << "_" << count2 << " true) (= penalty_" << count1 << "_" << count2 << " 0)))" << endl;
          ofp << "(assert (=>  (= cover_" << count1 << "_" << count2 << " false) (= penalty_" << count1 << "_" << count2 << " 1000)))" << endl;
      }
    }
  }
  ofp << endl;
  ofp << "(assert (= back true))" << endl;
  ofp << endl;
  */
}
