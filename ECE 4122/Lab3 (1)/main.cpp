
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
#include <mutex>
#include <thread>
#include <cstring>

using std::vector;
using std::thread;

std::mutex outFileMutex;
std::mutex inFileMutex;
std::fstream outFile;



class sudokuGrid
{
    public:
    friend std::fstream& operator<<(std::fstream& os, sudokuGrid & gridIn);
    friend std::fstream& operator>>(std::fstream& os, sudokuGrid & gridIn);

    int solve();
    std::string m_strGridName;
    unsigned char gridElement[9][9];
};


void solveSudoku();



int main(int argc, char* argv[])
{
    
    //std::vector<sudokuGrid> grids; //creating a vector of objects
      
    std::thread::hardware_concurrency();// number of threads that my system can handle

    std::cout<< std::thread::hardware_concurrency() << std::endl;



    sudokuGrid grid;

    std::fstream >> grid;

    

    
    
    
}


    

std::fstream& operator>>(std::fstream& os, sudokuGrid & gridIn)
{
   
    os.open("input_sudoku.txt");
    
    //while there is stuff to read from the file
    while(!os.eof())
    {
        getline(os, gridIn.m_strGridName);
        os >> gridIn.m_strGridName; 
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                os >> gridIn.gridElement[i][j];
                std::cout<<gridIn.gridElement[i][j]<<std::endl;
            }            
        }
    }
    return os;
}



std::fstream& operator<<(std::fstream& os, sudokuGrid & gridIn)
{
        os << ("out_sudoku.txt");
        getline(os, gridIn.m_strGridName);
       
        for(int i = 0; i < 9; i++)
        {  
            for(int j = 0; j < 9; j++)
            {
                os << gridIn.gridElement[i][j];
            }            
        }
    
    return os;
}


/*

int solveSudoku()
{
    
    
    do{
        
        
        
        
        
    }while(    );
    
   

    
    
    
}




*/



