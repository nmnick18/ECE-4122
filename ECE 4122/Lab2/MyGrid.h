#pragma once
#include <vector>
#include <string>
#include <fstream>


/* 
Author: Nikhil Malani
Class: ECE4122 
Last Date Modified: 10-1-2020, turning it in late, Hurley was fine with me turning it in late
Description:Pupose of this lab is to learn about oprator overloading
*/

using namespace std;

class MyGrid
{

public:
    //MyGrid(long const&, long const&, vector<vector<long> > const&);
    MyGrid();

    bool loadGridFromFile(const string& filename);
    void zeroOutGrid();

    //getters
    long getNumRows() const;
    long getNumCols() const;
    long getmyX() const;
    long getmyY() const;
    vector< vector<long> > getGridElements() const;

    MyGrid operator+(MyGrid const&) const;
    MyGrid operator-(MyGrid const&) const;

    MyGrid operator+(long const&) const;

    friend MyGrid operator+(long const& lhs, MyGrid const& rhs);

    // Addition assignment 
    MyGrid& operator+=(MyGrid const&);
    // Increment
    MyGrid& operator++(); // Prefix
    MyGrid operator++(int); // Postfix

    MyGrid& operator--(); // Prefix
    MyGrid operator--(int); // Postfix

    MyGrid operator-() const;

    bool operator==(MyGrid const&) const;

    friend fstream& operator<<(fstream& os, const MyGrid& gridIn);

private:
    long myX, myY;
    long row, column;
    vector< vector<long> > gridElements;
};

