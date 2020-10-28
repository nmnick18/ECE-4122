#include "sudokuGrid.h"

using namespace std;

/* 
Author: Nikhil Malani
Class: ECE4122 
Last Date Modified: 10-15-2020, turning it in late, Hurley was fine with me turning it in late
Description:Pupose of this lab is to learn about multi threading*/


fstream inFile;
fstream outFile;
mutex outFileMutex;
mutex inFileMutex;

using std::vector;
using std::thread;

void solveSudokuPuzzle()
{
    sudokuGrid Grid;
    do
    {
        inFileMutex.lock();
        inFile >> Grid;
        inFileMutex.unlock();
        Grid.solveSudoku();
        outFileMutex.lock();
        outFile << Grid;
        outFileMutex.unlock();;
    }while(!inFile.eof());
    inFileMutex.unlock();
}//end function

int sudokuGrid::getRow()
{
    return row;
}

int sudokuGrid::getCol()
{
    return col;
}


//this lab has a lot of the code from the tutorialpoint website that was given to use.
//SOME OF THE STUFF WAS COPY AND PASTED FROM THAT SITE AND SOME PARTS ARE GIVEN BY professor Hurley

bool sudokuGrid::solveSudoku()
{
   int row, col;
   if (!findEmptyPlace(row, col))
      return true; //when all places are filled
   for (int num = 1; num <= N; num++){ //valid numbers are 1 - 9
      if (isValidPlace(row, col, num)){ //check validation, if yes, put the number in the grid
         gridElement[row][col] = num;
         if (solveSudoku()) //recursively go for other rooms in the grid
            return true;
         gridElement[row][col] = 0; //turn to unassigned space when conditions are not satisfied
      }
   }
   return false;
}

//check to see if the number is present in the column
bool sudokuGrid::isPresentInCol(int col, int num)
{
    for(int row = 0; row < N; row++)
    {
        if(gridElement[row][col]== num)
        {
            return true;
        }
    }
    return false;
}

bool sudokuGrid::isValidPlace(int row, int col, int num)
{
   //when item not found in col, row and current 3x3 box
   return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3,col - col%3, num);
}

bool sudokuGrid::isPresentInRow(int row, int num)
{ //check whether num is present in row or not
   for (int col = 0; col < N; col++)
   {
      if (gridElement[row][col] == num)
      {
         return true;
      }
   }

   return false;
}

bool sudokuGrid::isPresentInBox(int boxStartRow, int boxStartCol, int num){
//check whether num is present in 3x3 box or not
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (gridElement[row+boxStartRow][col+boxStartCol] == num)
            return true;
   return false;
}

bool sudokuGrid::findEmptyPlace(int &row, int &col)
{ //get empty location and update row and column
   for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (gridElement[row][col] == 0) 
                return true;
   return false;
}

fstream& operator<<(fstream& os, sudokuGrid& gridIn)
{
    //output the solved grid 
	os << gridIn.m_strGridName << endl;
	for (int ii = 0; ii < N; ii++)
	{
		for (int jj = 0; jj < N ; jj++)
		{
			os << gridIn.gridElement[ii][jj];	
		}
		os << endl;
	}
	return os;
}


fstream& operator>>(fstream& os, sudokuGrid& gridIn)
{
    //input the grid to be solved
    string dataline;
    getline(os, gridIn.m_strGridName);
    char TempGrid[2];
    for (int i = 0; i < N; ++i)
    {
        getline(os, dataline);
        for (int j = 0; j < N; ++j)
        {
            TempGrid[0] = dataline[j];
            gridIn.gridElement[i][j] = atoi(TempGrid);
        }
    }
    return os;
}//end << operator function


int main(int argc, char* argv[])
{     
    //the amount of threads that can be ran minus 1
    int numthreads = thread::hardware_concurrency() - 1;
    //input and output files 
    inFile.open(argv[1], ios::in);
    outFile.open("Lab3Prob1.txt", ios::out); 

    //vector of threads 
    vector<thread> thds;

    thds.resize(numthreads);

    //give work to each thread and then close them
    for(int i = 0; i < numthreads; i++)
    {
        thds[i] = thread(solveSudokuPuzzle);
    }
    //give work to each thread and then close them
    for(int i = 0; i < numthreads; i++)
    {
        thds[i].join();
    }
    //close the file
   inFile.close();
   outFile.close();

}