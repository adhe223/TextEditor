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

	int input = 1;
	stringstream pos;

	//17 is the code for ctrl+q
	while (input != 17)
	{
		//Show the cursor location
		pos.str("");
		pos << "(" << file->getCursorY() << ", " << file->getCursorX() << ")";
		move(file->getNumRows(), 0);
		addstr(pos.str().c_str());

		//Make the cursor position flash
		move(file->getCursorY(), file->getCursorX());
		chgat(0, A_BLINK, 0, NULL);

		refresh();

		input = getch();

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
		else if (input == 260)
		{
			//Left Arrow
			if (file->getCursorX() > 0)
			{
				file->setCursorX(file->getCursorX() - 1);
			}
		}
		else if (input == 259)
		{
			//Up arrow
			if (file->getCursorY() > 0)
			{
				file->setCursorY(file->getCursorY() - 1);
			}

			//Now see if the X position needs to be changed(because of row widths)
			int currLength = file->getRowWidth(file->getCursorY());
			if (file->getCursorX() > currLength)
			{
				file->setCursorX(currLength);
			}
		}
		else if (input == 261)
		{
			//Right arrow
			if (file->getCursorX() <= file->getRowWidth(file->getCursorY()) - 1)
			{
				file->setCursorX(file->getCursorX() + 1);
			}
		}
		else if (input == 258)
		{
			//Down arrow
			if (file->getCursorY() < file->getNumRows() - 1)
			{
				file->setCursorY(file->getCursorY() + 1);
			}

			//Now see if the X position needs to be changed(because of row widths)
			int currLength = file->getRowWidth(file->getCursorY());
			if (file->getCursorX() > currLength)
			{
				file->setCursorX(currLength);
			}
		}
		else
		{
			/*//Input debug code
			stringstream ss;
			ss.str("");
			ss << input;
			clear();
			move(0, 0);
			addstr(ss.str().c_str());
			refresh();
			getch();*/

			//This will catch our quit command (17), so we have to exclude that
			if (input != 17)
			{
				file->insert(input);
			}
		}
		clear();
		file->display();
	}

	endwin();
	return 0;
}