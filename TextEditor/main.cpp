#include "File.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	//Take in the name of the file to open
	cout << "What file would you like to open?: ";

	string sFilename;
	cin >> sFilename;

	File * file = new File(sFilename);
	file->display();

	/*char input;
	while (input != '`')
	{
		//Display the file to the user and wait for input, then display again.
	}
	*/

	cin.ignore(200, '\n');
	cin.ignore(200, '\n');
	return 0;
}