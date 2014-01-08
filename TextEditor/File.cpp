#include "File.h"
#include <fstream>
#include <iostream>
#include <curses.h>
using namespace std;

File::File(string sFilename)
{
	cursor_pos_x = 0;
	cursor_pos_y = 0;

	m_sFilename = sFilename;
	ifstream file;
	file.open(sFilename);

	//Read in the content of file and place it into a 2D vector of chars
	string sLine;
	int iLine = 0;
	if (file.is_open())
	{
		while (getline(file, sLine))
		{
			vvcContent.push_back(vector<char>());
			for (int i = 0; i < sLine.length(); i++)
			{
				vvcContent[iLine].push_back(sLine[i]);
			}
			iLine++;
		}

		file.close();
	}
	else
	{
		cout << "Could not open your file!";
	}
}

void File::display()
{
	//Will use ncurses later, for now will simply loop and display
	for (int i = 0; i < vvcContent.size(); i++)
	{
		for (int j = 0; j < vvcContent[i].size(); j++)
		{
			move(i, j);
			addch(vvcContent[i][j]);
		}
	}
}

//Takes in the coordinate and the character to insert there
void File::insert(char cToInsert)
{
	int row = cursor_pos_y;
	int col = cursor_pos_x;

	//Add new character at the end of the row (value will be changed)
	vvcContent[row].push_back('-');

	//Shift all values at the coordinate and to the right in the row
	for (int j = vvcContent[row].size() - 1; j > col; j--)
	{
		vvcContent[row][j] = vvcContent[row][j - 1];
	}

	//Now set the coordinate to the value to insert
	vvcContent[row][col] = cToInsert;
}

//Takes in the coordinate of the character to delete
void File::del()
{
	//Make sure the row is not empty. If it is, then remove the row
	if (vvcContent[cursor_pos_y].size() <= 0) 
	{
		vvcContent.erase(vvcContent.begin() + cursor_pos_y);
		return;
	}

	vvcContent[cursor_pos_y].erase(vvcContent[cursor_pos_y].begin() + cursor_pos_x);
}

//Takes in the coordinate where a new line will be started
void File::enter()
{
	int row = cursor_pos_y;
	int col = cursor_pos_x;

	//Add new row vector to the end
	vvcContent.push_back(vector<char>());

	//Shift all the rows past the coordinate down
	for (int i = vvcContent.size() - 1; i > row; i--)
	{
		vvcContent[i] = vvcContent[i - 1];
	}

	//Now delete the leading characters that are in the row after the coordinate
	//row (it contains a copy of the coordinate row ATM)
	vvcContent[row + 1].erase(vvcContent[row + 1].begin(), vvcContent[row + 1].begin() + col);

	//Now delete the characters in the coordinate row following the coordinate
	vvcContent[row].erase(vvcContent[row].begin() + col, vvcContent[row].end());
}

void File::save()\
{
	//Open the output file (default will overwrite the existing)
	ofstream output(m_sFilename);

	//Write the data to the file
	for (int row = 0; row < vvcContent.size(); row++)
	{
		for (int col = 0; col < vvcContent[row].size(); col++)
		{
			output << vvcContent[row][col];
		}
		output << endl;
	}
	
}

int File::getCursorX()
{
	return cursor_pos_x;
}

int File::getCursorY()
{
	return cursor_pos_y;
}

void File::setCursorX(int x)
{
	cursor_pos_x = x;
}

void File::setCursorY(int y)
{
	cursor_pos_y = y;
}