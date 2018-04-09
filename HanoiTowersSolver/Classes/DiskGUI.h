#pragma once

#include <string>

using namespace std;


class DiskGUI
{
public:
	// Constructors
	DiskGUI();
	DiskGUI(string strLabel, POINT textCoor, RECT rect, int width, int height);

	// Getters and setters 
	POINT GetDiskCoordinate();
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	RECT GetRect();
	POINT GetTextCoor();
	string GetLabel();

	// Change disk coordinates
	void MoveCoordinateTo(int, int);

	~DiskGUI(void);
private:
	int width, height;
	RECT rect;
	POINT textCoor;
	string strLabel;
};
