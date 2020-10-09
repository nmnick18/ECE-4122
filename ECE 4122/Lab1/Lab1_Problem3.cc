#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <queue>

/* 
Author: Nikhil Malani
Class: ECE 4122
Last Date Modified: 9-14-2020
date : 9-12-2020
*/ 

/*

I finally got this to work, after some brute force and talking with peers, I finally got what I needed with a 2% uncertainty.

This lab was conceptually tough, I do enjoy this, but I would never want this during a coding interview
*/

//function declaration
double antpathtime(std::queue<int>, std::queue<int>);

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        //add value
        std::cout<<"add an argument"<<std::endl;
    }

    //convert value to a long unsigned number
    unsigned long num = strtol(argv[1], NULL, 10);

    //declare value for totalvelocity and radius and i counter
    double totalvelocity = 0;
    int i = 1;
    int rad = num/2;

    //make a queue for the list of x and y's
    std::queue <int> xlist;
    std::queue <int> ylist;

    //push(0,1)
    ylist.push(1);
    xlist.push(0);

    while (i<=num/2)
    {
        //find the exact y value and round it
        double pre_y = sqrt((rad*rad) - (rad-i)*(rad-i));
        int y = pre_y + 0.3;

        //push x and y to the queue
        xlist.push(i);
        ylist.push(y);

        //increment i for the new value
        i++;
    }

    //find the time
    totalvelocity = antpathtime(xlist, ylist);

    //display the velocity
    std::cout <<"the velocity: "<<totalvelocity << std::endl;

    //the value outputed to a text file
    std::ofstream output;
    output.open ("output3.txt");
    output << "the velocity value is: \n";
    output<<totalvelocity;
    output.close();
    return 0;
}

//create the ant path time function
double antpathtime(std::queue<int> x, std::queue<int> y)
{
    double totaltime = 0;

    //start from (0,1) to the next mid value
    int beginx = x.front();
    int beginy = y.front();

    //remove the first two values
    x.pop();
    y.pop();

    //use a while loop
    while (x.size() != 0)
    {
        //take the begin of the queue value
        int midx = x.front();
        int midy = y.front();
        //std::cout <<"mid path the x front: "<<x.front() << std::endl;
        //std::cout <<"mid path the y front: "<<y.front() << std::endl;

        //get the distance for the mid and beginning coordinates
        double distance = sqrt((midx - beginx)*(midx - beginx) + (midy - beginy)*(midy - beginy));
        double velocity = 0;

        // when the Ys are equal we only need the either y for the velocity
        if(midy == beginy)
        {
            velocity = beginy;
            totaltime = totaltime + (distance/velocity);
            //std::cout <<"time straight line: "<<totaltime<< std::endl;
        }

        //when the Ys do not equal, we want to use the equation given in the pdf to get the velocity
        else
        {
            velocity = ((midy - beginy)/ (log(midy) - log(beginy)));
            totaltime = totaltime + (distance/velocity);
            //std::cout <<"time not straight line: "<<totaltime<< std::endl;
        }

        beginx = midx;
        beginy = midy;

        x.pop();
        y.pop();
    }
    return totaltime*2;
}