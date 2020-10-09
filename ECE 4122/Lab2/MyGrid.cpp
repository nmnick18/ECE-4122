#include <iostream>
#include <vector>
#include <string>
#include "MyGrid.h"
#include  <fstream>
#include <cmath>
#include <assert.h>
#include <algorithm>

/* 
Author: Nikhil Malani
Class: ECE4122 
Last Date Modified: 10-1-2020, turning it in late, Hurley was fine with me turning it in late
Description:Pupose of this lab is to learn about oprator overloading*/

//default constructor, has all zeros
MyGrid::MyGrid():
	myX(0),
	myY(0),
    row(0),
    column(0),
	gridElements(0, vector<long>(0, 0))
{}

bool MyGrid::loadGridFromFile(const string& filename)
{    
    std::ifstream input;
    input.open(filename.c_str());

    if(!input.is_open())
    {
        return false;
    }

    input >> myX >> myY >> row >> column;

    //loop that takes in the input file grid
    gridElements.resize(row);
    for(int i =0; i < row; i++)
    {
        gridElements[i].resize(column);
        for(int j =0; j < column; j++)
        {
            input >> gridElements[i][j];
        } 
    }

    //std::cout<< "file opened" << std::endl;
    return true;
}//end function

void MyGrid::zeroOutGrid()
{
    //zero out the grid only
    for(int i = 0; i<row ; i++)
    {
        for (int j = 0; j < column; j++)
        {
            gridElements[i][j] = 0;
        }
    }
}

long MyGrid::getNumCols() const
{
    //get the column size, this is done by gridelement
    return gridElements[0].size();
}

long MyGrid::getNumRows() const
{
    //get the row size, you will need to add [0], to get row size.   
    return gridElements.size();
}

long MyGrid::getmyX() const
{
    //get the myX   
    return myX;
}

long MyGrid::getmyY() const
{
    //get the myX   
    return myY;
}

//stream operator
fstream &operator<<(fstream &os, const MyGrid &gridIn)
{
    //get the x and y
    os << gridIn.myX << " " << gridIn.myY << "\n";
    //get the row and column
    os << gridIn.row << " " << gridIn.column << "\n";

    //get grid elements
    for(int i = 0; i < gridIn.getNumRows(); i++)
    {
        for(int j = 0; j < gridIn.getNumCols(); j++)
        {
            os << gridIn.gridElements[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

//preincrement
MyGrid& MyGrid::operator++()
{
    //do a preincrement for each element
    for(int i = 0; i< this->getNumRows(); i++)
    {
        for (int j = 0; j < this->getNumCols(); j++)
        {
            ++this->gridElements[i][j];
        }
    }
    return *this;
}
//postincrement
MyGrid MyGrid::operator++(int)
{
    //do a postincrement for each element
    MyGrid tempGrid(*this);
    for(int i = 0; i<tempGrid.getNumRows(); i++)
    {
        for (int j = 0; j <tempGrid.getNumCols(); j++)
        {
            gridElements[i][j]++;
        }
    }
    return tempGrid;
} 

//predecrement
MyGrid& MyGrid::operator--()
{
    //predecrement for each gridelement
    //return *this grid
    for(int i = 0; i< this->getNumRows(); ++i)
    {
        for (int j = 0; j < this->getNumCols(); ++j)
        {
            --this->gridElements[i][j];
        }
    }
    return *this;
} 
//post-decrement
MyGrid MyGrid::operator--(int)
{
    MyGrid tempGrid(*this);
    //postdecrement for each gridelement
    //return the grid
    for(int i = 0; i<tempGrid.getNumRows(); i++)
    {
        for (int j = 0; j <tempGrid.getNumCols(); j++)
        {
            gridElements[i][j]--;
        }
    }
    return tempGrid;
}

MyGrid MyGrid::operator+(MyGrid const& rhs) const {

	MyGrid tempGrid;

    long bottomX, bottomY = 0;

    //get the Xs and Ys based on the top left and bottom right

	if (myX < rhs.myX)		//Check for the X
	{
		tempGrid.myX = myX; //get column as well
		bottomX = rhs.myX + rhs.column;
	}

	else{
        tempGrid.myX = rhs.myX;
		bottomX = myX + column;
    }


	if (myY > rhs.myY)		//Check for the Y
	{
		tempGrid.myY = myY;  
		bottomY = rhs.myY - rhs.row;
	}

	else{
		
        tempGrid.myY = rhs.myY;
		bottomY = myY - row;
	}

    
    //use the Xs and Ys to make the row and column
    tempGrid.row = abs(tempGrid.myY - bottomY);
    tempGrid.column = abs(tempGrid.myX - bottomX);

    vector< vector<int> > vec(tempGrid.row , vector<int> (tempGrid.column, 0));

    //add the gridElements with the current vector
    for (int i = 0; i < rhs.row; i++)
    {
        for (int j = 0; j < rhs.column; j++)
            vec[i][j + tempGrid.column - rhs.column] = (vec[i][j + tempGrid.column - rhs.column] + rhs.gridElements[i][j]);
    }

    //resize the grid
    tempGrid.gridElements.resize(tempGrid.row);
    for(int ii = 0; ii<tempGrid.row; ii++)
        tempGrid.gridElements[ii].resize(tempGrid.column);

    for (int i = 0; i < tempGrid.row; i++)
    {
        for (int j = 0; j < tempGrid.column; j++)
        {
            tempGrid.gridElements[i][j] = vec[i][j];
        }
    }
	return tempGrid;
}

MyGrid operator+(long const &lhs, MyGrid const &rhs) {  
	
    //create an object and pass in the rhs
    //create a nested for loop to add the constant long left hand to the gridelements on the right hand
    MyGrid tempGrid(rhs);
	for (int i = 0; i < tempGrid.getNumRows(); i++) 
    {
		for (int j = 0; j < tempGrid.getNumCols(); j++) 
        {
			tempGrid.gridElements[i][j] += lhs;
		}
	}
	return tempGrid;
}

MyGrid MyGrid::operator+(const long& rhs) const
{
    //add the constant of a long to each of the grid element
    MyGrid tempGrid(*this);
	for (int i = 0; i < tempGrid.getNumRows(); i++) 
    {
		for (int j = 0; j < tempGrid.getNumCols(); j++) 
        {
			tempGrid.gridElements[i][j] += rhs;
		}
	}
	return tempGrid;
}

MyGrid MyGrid::operator-() const 
{
    //create an object and take the current object passed in
    //do a nested for loop, to multiply by -1
    MyGrid tmpGrid(*this);

    for (int i = 0; i < tmpGrid.getNumRows(); i++)
    {
        for (int j = 0; j < tmpGrid.getNumCols(); j++)
        {
            tmpGrid.gridElements[i][j] =  tmpGrid.gridElements[i][j] * -1;
        }
        
    }
    return tmpGrid;
}

MyGrid MyGrid::operator-(MyGrid const &rhs) const 
{
	MyGrid tempGrid;

    long bottomX, bottomY;

	//get the Xs and Ys for the Bottom and Top corner
    if (myX < rhs.myX)		//Check for the X
	{
		tempGrid.myX = myX; //get column as well
		bottomX = rhs.myX + rhs.column;
	}

	else
	{
		tempGrid.myX = rhs.myX;
		bottomX = myX + column;
	}


	if (myY > rhs.myY)		//Check for the Y
	{
		tempGrid.myY = myY;  
		bottomY = rhs.myY - rhs.row;
	}

	else
	{
		tempGrid.myY = rhs.myY;
		bottomY = myY - row;
	}

    //get the boundary for rows and column 
    tempGrid.row = abs(tempGrid.myY - bottomY);
    tempGrid.column = abs(tempGrid.myX - bottomX);
    
    //create a new vector for the row and column
    vector< vector<int> > grid(tempGrid.row , vector<int> (tempGrid.column, 0));

    //add the gridElements with the current vector
    for (int i = 0; i < rhs.row; i++)
    {
        for (int j = 0; j < rhs.column; j++)
            grid[i][j + tempGrid.column - rhs.column] = abs(grid[i][j + tempGrid.column - rhs.column] - rhs.gridElements[i][j]);
    }

    //resize the grid
    tempGrid.gridElements.resize(tempGrid.row);
    for(int ii = 0; ii<tempGrid.row; ii++)
        tempGrid.gridElements[ii].resize(tempGrid.column);

    for (int i = 0; i < tempGrid.row; i++)
    {
        for (int j = 0; j < tempGrid.column; j++)
        {
            tempGrid.gridElements[i][j] = grid[i][j];
        }
    }

	return tempGrid;
}

MyGrid& MyGrid::operator+=(MyGrid const &b) 
{
    //you will need to equal the this to the b since it will be the same from seeing the main.cpp
    *this = b;
	return *this;
}

bool MyGrid::operator==(MyGrid const &rhs) const 
{
    
    //write a condition that allows you to check the Xs and Ys and the row and column
    //write a condition inside to check each gridelements
    MyGrid tmpGrid(*this);
    if(tmpGrid.myX == rhs.myX 
    && tmpGrid.myY == rhs.myY 
    && tmpGrid.row == rhs.row 
    && tmpGrid.column == rhs.column)
    {
        for (int i = 0; i < tmpGrid.getNumRows(); i++)
        {
            for (int j = 0; i < tmpGrid.getNumCols(); j++)
            {
                if(tmpGrid.gridElements[i][j] == rhs.gridElements[i][j])
                {
                    return true;
                }
            } 
            
        }
    }
    //return false if its not equal
    else{
        return false;
    }

}


