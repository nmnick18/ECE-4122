#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <fstream>
#include <random>
#include <thread>


using std::thread;
using std::vector;

/* 
Author: Nikhil Malani
Class: ECE4122 
Last Date Modified: 10-15-2020, turning it in late, Hurley was fine with me turning it in late
Description:Pupose of this lab is to learn about OpenMP*/

vector<double> getTheXs(int N)
{   
   // const int iNUM_THREADS = std::thread::hardware_concurrency() / 2;

    double x1, x2, x3, z = 0; //declare private
    double max_X1, max_X2, max_X3, maxZ = 0;
    vector<double> Xs;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> X1Dist(0.0,1.0);//range 0 to 1
    std::uniform_real_distribution<double> X2Dist(1.0,2.0);//range 1 to 2
    std::uniform_real_distribution<double> X3Dist(2.0,3.0);//range 2 to 3

    long ii = 0;

    #pragma omp parallel
    {
    
        #pragma omp parallel for private(x1,x2,x3,z)
        for(int i = 1; i <= N; i++)
        {
            //generate random numbers for the Xs
            x1 = X1Dist(generator);
            x2 = X2Dist(generator);
            x3 = X3Dist(generator);

            //get the z value

            z = (exp(x1)+x2)*(exp(x1)+x2) + (3*((1-x3) * (1-x3))); //equation
            //now get the maxZ along with the max Xs, this should pan out and get around the 1,2,3
            #pragma omp critical
            if(z > maxZ)
            {
                max_X1 = x1;
                max_X2 = x2;
                max_X3 = x3;
                maxZ = z;
            }
        }
             
     }//end pragma

    //use a vector and add in the Xs
    Xs.push_back(max_X1);
    Xs.push_back(max_X2);
    Xs.push_back(max_X3);
    //return the Xs
    return Xs;

}//end function

int main(int argc, char* argv[]) 
{
    std::ofstream output;
    output.open("Lab3Prob3.txt");

    int N;
    
    for (int i = 1; i < argc; i++)
    {
        std::string args = argv[i];
        if (args == "-N" || args == "N" || args == "-n" || args == "n")
        {
            N = strtol(argv[i+1], NULL, 10); 
        }
        else
        {
            N = strtol(argv[i], NULL, 10);   
        }
    } 

    //use a vector to put all the Xs in

    vector<double> Xs;
    Xs.resize(3);
    Xs = getTheXs(N);

    //print the Xs
    output << "X1: " << Xs[0] << "\n";
    output << "X2: " << Xs[1] << "\n";
    output << "X3: " << Xs[2] << "\n";
    output.close();
    
    return 0;
}
