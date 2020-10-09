#include<iostream>
#include <stdlib.h>
#include <fstream>

/* 
Author: Nikhil Malani
Class: ECE 4122
Last Date Modified: 9-12-2020
date : 9-12-2020
*/ 


int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        //add value
        std::cout<<"add an argument"<<std::endl;
        std::cout<<"example: ./a.out <integer value>"<<std::endl;
    }

    //use the usigned long to get the number
    unsigned long num = atol(argv[1]);
    
    //start the sum with the sum value
    unsigned long sum = num;

    std::cout<<"\n"<<std::endl;

    std::cout<<num;

    //run a while loop until num is 1
    while (num != 1)
    {
        //if the value is even divide by 2 then add it to sum
        if(num%2 == 0)
        {
            num = num/2;
            std::cout<<"-->"<< num;
            sum = sum + num;
        }
        //if it is odd multiply by 3 and add 1, also add to the sum
        else
        {
            num = (3*num) + 1;
            std::cout<<"-->"<< num;
            sum = sum + num;
        }
    }

    std::cout<<"\n"<<std::endl;

    //print the output of the sum to a text file called output2.txt
    std::ofstream output;
    output.open("output2.txt");
    output<<sum;
    output.close();
    return 0;
}
