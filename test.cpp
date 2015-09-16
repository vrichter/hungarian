/********************************************************************
 ********************************************************************
 ** C++ class implementation of the Hungarian algorithm by David Schwarz, 2012
 **
 **
 ** O(n^3) implementation derived from libhungarian by Cyrill Stachniss, 2004
 **
 **
 ** Solving the Minimum Assignment Problem using the
 ** Hungarian Method.
 **
 ** ** This file may be freely copied and distributed! **
 **
 **
 ** This file is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied
 ** warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 ** PURPOSE.  
 **
 ********************************************************************
 ********************************************************************/

#include "hungarian.hpp"

std::vector< std::vector<int> > array_to_matrix(const int* m, int rows, int cols) {
  int i,j;
  std::vector< std::vector<int> > r;
  r.resize(rows, std::vector<int>(cols, 0));

  for(i=0;i<rows;i++)
  {
    for(j=0;j<cols;j++)
      r[i][j] = m[i*cols+j];
  }
  return r;
}

void do_test(const int* cost_matrix, int rows, int columns,
             const int* expected_assignment,
             bool verbose=1)
{
  std::vector<std::vector<int> > m = array_to_matrix(cost_matrix,4,3);

  /* initialize the gungarian_problem using the cost matrix*/
  Hungarian hungarian(m , 4,3, HUNGARIAN_MODE_MINIMIZE_COST) ;
  if(verbose){
    std::cerr << "Created cost matrix:\n";
    hungarian.print_cost();
  }
  hungarian.solve();
  if(verbose){
    std::cerr << "Calculated Assignment matrix:\n";
    hungarian.print_assignment();
  }
  const std::vector<std::vector<int> >& assignment = hungarian.assignment();
  const int* expected_assignment_position = expected_assignment;
  for(unsigned int row = 0; row < rows; ++row){
    for (unsigned int column = 0; column < columns; ++column, ++expected_assignment_position){
      if(assignment[row][column] != *expected_assignment_position){
        std::cerr << "Test failed for cost matrix:\n";
        hungarian.print_cost();
        std::cerr << "Assignment:\n";
        hungarian.print_assignment();
        std::cerr << "Assignment in row = " << row << " column = " << column << " not expected." << std::endl;
        return;
      }
    }
  }
  std::cerr << "Test passed." << std::endl;
}

int main() {

  {
  // test 1
  std::cerr << "Test #" << 1 << std::endl;
  int cost[4*3] =  {   100,   100,     1,
                       100,     2, 21512,
                         1,     4,  9852,
                         6, 30252,   400 };

  int assign[4*3] = {    0,     0,     1,
                         0,     1,     0,
                         1,     0,     0,
                         0,     0,     0};

  do_test(cost,4,3,assign,false);
  }

  {
  // test 2
  std::cerr << "Test #" << 2 << std::endl;
  int cost[2*2] =  { 2, 0,
                     1, 0 };

  int assign[2*2] = { 0, 0,
                      0, 1 };


  do_test(cost,2,2,assign,false);
  }

  {
  // test 3
  std::cerr << "Test #" << 3 << std::endl;
  int cost[4*4] = {20,20,10,10,
                   10,10,30,20,
                   10,10,10,20,
                   20,20,30,10};

  int assign[4*4] = {0,0,1,0,
                     1,0,0,0,
                     0,1,0,0,
                     0,0,0,1};

  do_test(cost,4,4,assign,true);
  }



  return 0;
}

