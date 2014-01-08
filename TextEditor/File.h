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
	void insert(char cToInsert);
	void del();
	void enter();
	void save();

	int getCursorX();
	int getCursorY();
	void setCursorX(int x);
	void setCursorY(int y);
	int getRowWidth(int row);
	int getNumRows();

private:
	//The first index is the row, the second index is the column (*NOTE* ncurses takes
	//this in the opposite order).
	std::vector<std::vector<char>> vvcContent;
	std::string m_sFilename;
	int cursor_pos_x;
	int cursor_pos_y;
};

#endif