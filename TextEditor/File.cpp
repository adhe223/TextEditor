#include "File.h"
#include <fstream>
#include <iostream>
using namespace std;

File::File(string sFilename)
{
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
			cout << vvcContent[i][j];
		}
		cout << endl;
	}
}