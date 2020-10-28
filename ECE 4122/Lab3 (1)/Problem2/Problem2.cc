#include <iostream>
#include <cmath>
#include <omp.h>
#include <cstring>
#include <random>
#include <fstream>

/* 
Author: Nikhil Malani
Class: ECE4122 
Last Date Modified: 10-15-2020, turning it in late, Hurley was fine with me turning it in late
Description:Pupose of this lab is to learn about OpenMP*/

int main(int argc, char* argv[]) 
{
    //get the command line arguments to be put in N and G
    unsigned long N;
    unsigned long GridNum;

    std::ofstream output;
    output.open("Lab3Prob2.txt");

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,4);

    
    //load from the argument the number of steps and grid size
    for (int i = 1; i < argc; i++)
    {
        std::string args = argv[i];
        if (args == "-N" || args == "N" || args == "-n" || args == "n")
            N = strtol(argv[i+1], NULL, 10); 
        if(args == "-g" || args == "-G" || args == "G" || args == "g")
            GridNum = strtol(argv[i+1], NULL, 10); 
    }

    //initialize a grid with the grid size
    int grid[GridNum][GridNum];
    //initialize a direction variable
    int direction;
    //create a stuck and success counter and a max sucess and stuck
    double successPath, stuckPath = 0;
    double maxSuccess, maxStuckPath = 0;

    #pragma omp parallel 
    {
        long numThread = omp_get_num_threads(); //get the total number of threads
        omp_set_num_threads(numThread - 1);
        
            #pragma omp parallel for reduction(+:successPath) schedule(static)
            for(int i = 0; i < N; i++)
            {
                //create the row and col that start at (1,1)
                int  ii = 1;
                int  jj = 1;

                //initialize every in the grid as a zero
                std::memset(grid, 0, sizeof grid);

                grid[ii][jj] = 1;//starting position is visited

                while(true)
                {
                    direction = distribution(generator); // roll between 1 to 4
                    //If the direction is to go up
                    if(direction == 1 && grid[ii][jj-1] == 0)
                        if(jj-1<= GridNum && jj-1 >= 1)
                        {
                            jj--;
                            grid[ii][jj] = 1; 
                        }
                        else{continue;}
                    //If the direction is to go down
                    else if(direction == 2 && grid[ii][jj+1] == 0)
                        if(jj+1<= GridNum && jj+1 >= 1)
                        {
                            jj++;
                            grid[ii][jj] = 1;
                        }
                        else{continue;}
                    //If the direction is to go left 
                    else if(direction == 3 && grid[ii-1][jj] == 0)
                        if(ii-1 >= 1 && ii-1<= GridNum)
                        {
                            ii--;
                            grid[ii][jj] = 1;
                        }
                        else{continue;}
                    //If the direction is to go right
                    else if (direction == 4 && grid[ii+1][jj] == 0)
                        if(ii+1 >= 1 && ii+1<= GridNum)
                        {
                            ii++;
                            grid[ii][jj] = 1;
                        }
                        else{continue;}  
                    //last part is to check if it is stuck
                    else
                    {
                        if (ii-1 < 1 || ii+1 > GridNum || jj-1 < 1 || jj+1 > GridNum)
                        {
                            stuckPath++;
                            break;   
                        }
                        else
                        {
                            successPath++;
                            break;
                        }
                    }
                }

                if(successPath > maxSuccess)
                {
                    maxSuccess = successPath;
                    maxStuckPath = stuckPath;
                }
            }
    }       
    double PP = (maxSuccess/N);
    output << "Success: " << maxSuccess << "\n";
    output << "The Probability: "<< PP << "\n";

    return 0;
}