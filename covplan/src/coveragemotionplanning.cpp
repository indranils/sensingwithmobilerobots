#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "primitive.h"
#include "readinputs.h"
#include "writeconstraints.h"
#include "extractoutput.h"
#include "definepropositions.h"
#include "generatecoverageconstraints.h"

using namespace std;

const unsigned int max_traj_length = 20;


void printTimeDifference(double wcts, double wcte) 
{
  double duration;
  int hr, min;
  double sec;

  duration = wcte - wcts;
  hr = duration / 3600;
  min = (duration / 60) - (hr * 60) ;
  sec = duration - hr * 3600 - min * 60;
  cout << endl << duration << "s" << endl;
  cout << endl << hr << "h " << min << "m " << (((sec - int(sec)) > 0.5) ? (int(sec) + 1) : int(sec)) << "s" << endl << endl;

  ofstream ofp;
  ofp.open("result", fstream::app); 
  ofp << hr << "h " << min << "m " << (((sec - int(sec)) > 0.5) ? (int(sec) + 1) : int(sec)) << "s" << endl << endl;
  ofp.close();
}


void generateZ3File(prim_vec_t primitives, dimension_t dimension, pos_vec_t obstacles, pos_vec_t initpos, int trajectory_length, float cost)
{
  ofstream ofp;
  ifstream ofpr;
  string line;

  ofp.open("constraints.smt2");

  /* Declare the variables */
  declareVariables(ofp, initpos.size(), trajectory_length + 1);
  ofp << endl << endl;

  declarePropositions(ofp, dimension, obstacles, initpos.size(), trajectory_length + 1);
  
  declarePenaltyVariables(ofp, dimension, obstacles);
  
  /* Write the General Constraints */
  writeInitialLocationConstraints(ofp, initpos);
  ofp << endl;

  writeObstacleConstraints(ofp, dimension, obstacles, initpos.size(), trajectory_length + 1);
  ofp << endl;

  writeTransitionConstraints(ofp, primitives, dimension, obstacles, initpos.size(), trajectory_length + 1);
  ofp << endl;

  writeCollisionAvoidanceConstraints2(ofp, primitives, initpos.size(), trajectory_length + 1);
  ofp << endl;

  //writeDistanceConstraints(ofp, initpos.size(), trajectory_length + 1);
  //ofp << endl;

  writeCostConstraint(ofp, dimension, obstacles, initpos.size(), trajectory_length + 1, cost);
  ofp << endl;


  /* Write the specification constraints */
  definePropositions(ofp, dimension, obstacles, initpos.size(), trajectory_length + 1);
  ofp << endl << endl;
  
  /*ofpr.open("ltlconstraints.txt");
  if (ofpr.is_open())
  {
    while(std::getline(ofpr, line))
    {
      std::istringstream iss(line);
      ofp << line << endl;
    }
  }
  ofpr.close();
  ofp << endl << endl;
  
  writeLoopConstraints(ofp, number_of_robots, trajectory_length + 1);
  writeStateLoopConstraints(ofp, workspace);
  */

  writeCoverageConstraints(ofp, dimension, obstacles, initpos.size(), trajectory_length + 1);

  ofp << "(check-sat)" << endl;
  //ofp << "(get-model)" << endl;
  writeOutputConstraints(ofp, initpos.size(), trajectory_length + 1);
  //writeLoopOutputConstraints(ofp, workspace);

  ofp.close();
}


void generateTrajectories(prim_vec_t primitives, dimension_t dimension, pos_vec_t obstacles, pos_vec_t initpos)
{
  unsigned int count;
  int number_of_free_locations;
  float max_total_cost, min_total_cost, current_cost;
  

  ifstream ifp;
  string line;
  bool sat_flag;

  number_of_free_locations = dimension.length_x * dimension.length_y - obstacles.size();

  cout << "Number of Free Locations: " << number_of_free_locations << endl << endl;

  count = 2;
  while (count < max_traj_length)
  {
    generateZ3File(primitives, dimension, obstacles, initpos, count, number_of_free_locations * 1000);
    system("z3 constraints.smt2 > z3_output");

    ifp.open("z3_output");
    getline(ifp, line);
    ifp.close();
    cout << "$$$$$$$$ " << count << " " << line << endl;

    if (line == "unsat")
    {
      cout << "11111111" << endl;
      count = count + 1;
      continue;
    }
    else
    {
      max_total_cost = extractTrajectoryCostInformation();
      min_total_cost = 0;
      current_cost = (max_total_cost + min_total_cost) / 2;
    }

    cout << "max_total_cost = " << max_total_cost << endl;
    cout << "min_total_cost = " << min_total_cost << endl;
    cout << "current_cost  = " << current_cost << endl;

    /*
    while (max_total_cost - min_total_cost > 1)
    {
      generateZ3File(primitives, dimension, obstacles, initpos, count, current_cost);
      system("z3 constraints.smt2 > z3_output");

      ifp.open("z3_output");
      getline(ifp, line);
      ifp.close();
      cout << "$$$$$$$$ " << count << " " << line << endl;

      if (line == "unsat")
      {
        min_total_cost = current_cost;
      }
      else if (line == "sat")
      {
        sat_flag = true;
        max_total_cost = extractTrajectoryCostInformation();
        system("mv z3_output z3_output_sat");
      }
      else
      {
        cout << "unknown output from z3.." << endl;
        min_total_cost = current_cost;
        if (sat_flag == true)
          break;
      }
      current_cost = (max_total_cost + min_total_cost) / 2;
      cout << "max_total_cost = " << max_total_cost << endl;
      cout << "min_total_cost = " << min_total_cost << endl;
      cout << "current_cost  = " << current_cost << endl;
    }
    count = count + 1;
    system("mv z3_output_sat z3_output");
    */
    break;
  }
}


void printTrajectories(int number_of_robots)
{
  int count, count1;
  vector<int> x_arr, y_arr, prim_arr;

  cout << endl<< "Trajectories:" << endl << endl;
  for (count = 1; count <= number_of_robots; count++)
  {
    x_arr.clear();
    y_arr.clear();
    prim_arr.clear();
    cout << "Robot " << count << endl;
    extractTrajectoryInformation(count, x_arr, y_arr , prim_arr);
    for (count1 = 0; count1 < x_arr.size(); count1++)
    {
      cout << x_arr[count1] << " " << y_arr[count1] << endl;
    }
    cout << endl;
  }
}


int main ()
{
  prim_vec_t primitives;
  dimension_t dimension;
  pos_vec_t obstacles;
  pos_vec_t initpos;
  ofstream ofp;

  readPrimitives(primitives);
  //writePrimitives(primitives);

  readDimension(dimension);
  //writeDimension(dimension);

  readPositions(obstacles, "obstacle.txt");
  cout << "Positions of the Obstacles:" << endl;
  writePositions(obstacles);

  readPositions(initpos, "initpos.txt");
  cout << "Initial Positions of the Robots:" << endl;
  writePositions(initpos);

  struct timeval tm;
  double wcts, wcte;

  gettimeofday( &tm, NULL );
  wcts = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  generateTrajectories(primitives, dimension, obstacles, initpos);
  gettimeofday( &tm, NULL );
  wcte = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  ofp.open("result", fstream::app);
  ofp << "Total Time Before Optimization = ";
  ofp.close();
  printTimeDifference(wcts, wcte);

  printTrajectories(initpos.size());
}
