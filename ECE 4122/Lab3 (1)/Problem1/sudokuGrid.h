#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
#include <mutex>
#include <thread>
#include <queue> 
#include <cstring>
#define N 9


//This header file holds the class of all the objects that are used in the problem 1
class sudokuGrid
{
    public:
        bool isValidPlace(int, int, int);
        bool solveSudoku();
        bool isPresentInBox(int, int, int);
        bool findEmptyPlace(int&, int&);
        friend std::fstream& operator>>(std::fstream& os, sudokuGrid & gridIn);
        friend std::fstream& operator<<(std::fstream& os, sudokuGrid & gridIn);
        
        int getRow();
        int getCol();
    private:

        bool isPresentInCol(int, int);
        bool isPresentInRow(int, int);

        std::string m_strGridName;
        int gridElement[N][N];
        int row;
        int col;
        int num;

};