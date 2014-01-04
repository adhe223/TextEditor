#ifndef FILE_H
#define FILE_H

#include <vector>
#include <string>

class File
{
public:
	File(std::string sFilename);
	~File();

	void display();

private:
	//The first index is the row, the second index is the column (*NOTE* ncurses takes
	//this in the opposite order).
	std::vector<std::vector<char>> vvcContent;
};

#endif