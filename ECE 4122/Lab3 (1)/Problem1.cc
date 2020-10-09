#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <mutex>

/* 
Author: Nikhil Malani
your nameClass: ECE 4122
Last Date Modified: 8-27-2020
date : 8-27-2020
Description: 
Need to create a sudoku solver, we need to pass the file in with the right vector size. 

Idea is to load in the a 9x9 grid, then solve that, and use a while loop to repeat that.
*/ 

using std::vector;
using namespace std;

vector< vector<int>> vec(9 , vector<int> (9, 0));

std::mutex outFileMutex;
std::mutex inFileMutex;
std::fstream outFile;
std::fstream inFile;


class SudokuGrid
{
public:

	string getGridName();
	unsigned char getElement(int x, int y) const;
	SudokuGrid solve();
	//reads a single SudokuGrid object from a fstream file.
	friend fstream& operator>>(fstream& os, const SudokuGrid & gridIn);
	//writes the SudokuGrid object to a file in the same format that is used in reading in the object.
	friend fstream& operator<<(fstream& os, const SudokuGrid & gridIn);


private:
	string m_strGridName;
	unsigned char gridElement[9][9];
};

string getGridName()
{}



bool loadSudoku(string& filename)
{
     string grid;
     int version;
     std::ifstream input;
     
     input.open(filename.c_str());
     if(input.is_open())
     {
        input >> grid >> version;

        for (size_t i = 0; i < vec.size(); i++)
        {
            for (int j = 0; j < vec[0].size(); j++)
            {
                input >> vec[i][j];
            }
            
        }
        return true;
     }

     else
     {
        return false;
     }
}

//EVERYTHING FROM HERE ONWARDS IS FROM TUTORIAL POINT THAT WAS GIVEN TO US BY PROFESSOR HURLEY

bool isPresentInCol(int col, int num){ //check whether num is present in col or not
   for (int row = 0; row < vec.size(); row++)
      if (vec[row][col] == num)
         return true;
   return false;
}
bool isPresentInRow(int row, int num){ //check whether num is present in row or not
   for (int col = 0; col < vec[0].size(); col++)
      if (vec[row][col] == num)
         return true;
   return false;
}
bool isPresentInBox(int boxStartRow, int boxStartCol, int num){
//check whether num is present in 3x3 box or not
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (vec[row+boxStartRow][col+boxStartCol] == num)
            return true;
   return false;
}
void sudokuGrid(){ //print the sudoku grid after solve
   for (int row = 0; row < vec.size(); row++){
      for (int col = 0; col < vec[0].size(); col++){
         if(col == 3 || col == 6)
            cout << " | ";
         cout << vec[row][col] <<" ";
      }
      if(row == 2 || row == 5){
         cout << endl;
         for(int i = 0; i<vec.size(); i++)
            cout << "---";
      }
      cout << endl;
   }
}
bool findEmptyPlace(int &row, int &col){ //get empty location and update row and column
   for (row = 0; row < vec.size(); row++)
      for (col = 0; col < vec[0].size(); col++)
         if (vec[row][col] == 0) //marked with 0 is empty
            return true;
   return false;
}
bool isValidPlace(int row, int col, int num){
   //when item not found in col, row and current 3x3 box
   return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,
col - col%3, num);
}
bool solveSudoku(){
   int row, col;
   if (!findEmptyPlace(row, col))
      return true; //when all places are filled
   for (int num = 1; num <= 9; num++){ //valid numbers are 1 - 9
      if (isValidPlace(row, col, num)){ //check validation, if yes, put the number in the grid
         vec[row][col] = num;
         if (solveSudoku()) //recursively go for other rooms in the grid
            return true;
         vec[row][col] = 0; //turn to unassigned space when conditions are not satisfied
      }
   }
   return false;
}


int main(int argc, char* argv[]) {

    std::string file = argv[1];
    
    while (loadSudoku(file) == true)
    {
        /* code */
    }
}