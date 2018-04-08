#include "stdafx.h"
#include "DiskGUI.h"

DiskGUI::DiskGUI()
{
}

DiskGUI::DiskGUI(string strLabel, POINT textCoordinate, RECT rect, int width, int height)
{
	this->strLabel = strLabel;
	this->textCoor = textCoordinate;
	this->rect = rect;
	this->width = width;
	this->height = height;
}

POINT DiskGUI::GetPlateCoordinate()
{
	POINT coord;
	coord.x = this->rect.left;
	coord.y = this->rect.top;
	return coord;
}

int DiskGUI::GetX()
{
	return this->rect.left;
}

int DiskGUI::GetY()
{
	return this->rect.top;
}

int DiskGUI::GetWidth()
{
	return this->width;
}

int DiskGUI::GetHeight()
{
	return this->height;
}

void DiskGUI::MoveCoordinateTo(int x, int y)
{
	this->rect.left = x;
	this->rect.top = y;
	this->rect.right = x + this->width;
	this->rect.bottom = y + this->height;
}

POINT DiskGUI::GetTextCoor()
{
	return this->textCoor;
}

RECT DiskGUI::GetRect()
{
	return this->rect;
}

string DiskGUI::GetLabel()
{
	return this->strLabel;
}

DiskGUI::~DiskGUI(void)
{
	// do nothing
}