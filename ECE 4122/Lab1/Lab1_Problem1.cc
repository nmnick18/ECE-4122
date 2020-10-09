#include<iostream>
#include <stdlib.h>
#include <fstream>

/* 
Author: Nikhil Malani
Class: ECE 4122
Last Date Modified: 9-11-2020
date : 9-10-2020
*/ 

//function to check if it is prime
bool isPrime(long Num)
{
    //if the number is 0 or 1, return false
    if(Num <= 1) { 
        return false; 
    } 
    //iterate thru and check if the any value has no remaider
    for (int i = 2; i*i <= Num; i++) { 
        if (Num % i == 0) { 
            return false; 
        } 
    } 
    return true; 
}

long PrimeSum(long);

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        //add value
        std::cout<<"add an argument"<<std::endl;
        std::cout<<"example: ./a.out <integer value>"<<std::endl;
    }
    //convert char to long value
    long arg = atol(argv[1]);

    //used for counting the prime value
    int totalPrime = 0;

    //put the arg into prime sum to get all the prime values to be added
    totalPrime = PrimeSum(arg);
    //subtract 1 since it takes in the 1
    totalPrime = totalPrime -1;

    //get a off stream to add values to a text file
    std::ofstream output;
    output.open ("output1.txt");
    output << "sum of prime number: \n";
    output<<totalPrime;
    output.close();
    return 0;


}

//function to get the prime values
long PrimeSum(long Num)
{
    long sum = 0;

    for (int i = Num; i >= 0; i--)
    {
        bool checkPrime = isPrime(i);

        if (checkPrime == true)
        {
            sum = sum + i;
        }
        
    }
    return sum;
}
