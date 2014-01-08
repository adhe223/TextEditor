#include "File.h"
#include <iostream>
#include <sstream>
#include <string>
#include <curses.h>
using namespace std;

int main()
{
	//Take in the name of the file to open
	cout << "What file would you like to open?: ";

	string sFilename;
	cin >> sFilename;

	File * file = new File(sFilename);

	initscr();
	keypad(stdscr, TRUE);
	clear();

	file->display();

	char input = '!';
	//int row = 0;
	//int col = 0;

	while (input != '`')
	{
		int input = getch();

		if (input == 330)
		{
			file->del();
		}
		else if (input == '\n')
		{
			file->enter();
		}
		else if (input == 19)
		{
			file->save();
		}
		else
		{
			file->insert(input);
		}
		clear();
		file->display();
	}

	cin.ignore(200, '\n');
	cin.ignore(200, '\n');
	return 0;
}