/*
Author: Will Stull
Class: ECE4122
Last Date Modified:
Description:
*/
#pragma once
#include <fstream>
#include <string>
#include <thread>

using namespace std;

class SudokuGrid
{
public:

	string getGridName() const;
	void setGridName(string gridName);
	unsigned char getElement(int x, int y) const;
	void setElement(int x, int y, unsigned char element);
	SudokuGrid solve();
	//reads a single SudokuGrid object from a fstream file.
	friend fstream& operator>>(fstream& os, const SudokuGrid & gridIn);
	//writes the SudokuGrid object to a file in the same format that is used in reading in the object.
	friend fstream& operator<<(fstream& os, const SudokuGrid & gridIn);
private:
	string m_strGridName;
	unsigned char gridElement[9][9];
};