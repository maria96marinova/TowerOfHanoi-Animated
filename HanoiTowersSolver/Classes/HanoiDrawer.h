#pragma once

#include "BuilderExtensions.h"
#include "DiskGUI.h"
#include <list>
#include <cmath>

#define LIST_ELEMENT_NOT_FOUND -1

using namespace std;

class HanoiDrawer
{
public:
	
	// Represents the tower
	enum Tower
	{
		Nothing = -1,
		No1 = 0,
		No2 = 1,
		No3 = 2
	};

	// Used for specify the coordinates
	struct PointF
	{
		PointF()
		{
			x = y = 0;
		}

		PointF(double dx,double dy)
		{
			x = dx;
			y = dy;
		}

		double x, y;
	};

	// constants
	static const int DEFAULT_Disks_COUNT
		, DEFAULT_STEP_TIME
		, SOURCE
		, DESTINATION
		, INTERMEDIATE
		, TOWER_WIDTH
		, TOWER_HEIGHT		
		, DISK_HEIGHT
		, INIT_DISKS_COUNT
		, MAX_DISKS_COUNT
		, MIN_DISKS_COUNT
		, MAX_STEP_TIME_IN_SECONDS
		, MIN_STEP_TIME_IN_SECONDS
		;

	// Constructor
	HanoiDrawer();
	HanoiDrawer(HDC);
	HanoiDrawer(HDC, int);
	HanoiDrawer(HDC, int, bool, int);

	// Adjust tower in App main window
	void SetTowerCoordinates(Tower, int, int);
	// Advance one step to solve Hanoi
	void SolveNextStep();

	void DrawTowers();
	void DrawDisks();

	// Draws towers and Disks
	void ReDraw();

	/* Setters and getters*/
	int GetMovesCount();
	int GetTotalMovesCount();
	bool GetAutoSolveAction();
	int GetDisksCount();
	void SetAutoSolveAction(bool);
	void SetOwnerInstance(HINSTANCE);
	void SetOwner(HWND);
	void SetHDC(HDC);
	void SetCountContainer(int);
	void SetFromTextContainer(int);
	void SetToTextContainer(int);
	void SetThroughTextContainer(int);
	void SetDisksCount(int);
	void SetStepTime(int);
	bool autoSolve;
	int GetStepTime();
	

	// Display information about the current step in the main window
	void ShowCurrentStepInfo();
	// Hide information about the current step from the main window
	void HideCurrentStepInfo();

	// Draws a given disk in the main window
	void DrawGUIDisk(string, POINT, RECT);

	// Invalidate the area of drawing
	void Invalidate();
	// did we finish solving the problem
	bool IsSolved();

	~HanoiDrawer();
private:

	// lists save the tower
	// of each disk
	list<int> tower1
		, tower2
		, tower3
		// list of integers each 4 integers represent a step
		// each step consist of :
		//				- number of disks
		//				- index of the current source
		//				- index of the current destination
		//				- index of the current intermediate
		, listSavedState;

	// lists of pointers to Disk objects save the visual appearance
	// of each disk in its corresponding
	// tower
	list<DiskGUI*> listTower1GUI, listTower2GUI, listTower3GUI;


	bool proceedNextStep
		, solved;
	// Coordinates of the three towers
	PointF arrTowersCoord[3];

	int iDisksCount, iMovesCount, iStepTime
		, countContainerResourceId
		, fromContainerResourceId
		, toContainerResourceId
		, throughContainerResourceId ;
	

	HINSTANCE hInstance;
	HWND hWnd;
	HDC hdc;

	// Draws the initial state
	void PopulateDisksList();

	// Draws a tower
	void DrawOneTower(Tower);

	// Draws disks in a given tower
	void DrawDisks(Tower, list<int>);

	// Related to DrawDisks by doing
	// the low level tasks
	void DrawDisksInList(Tower, list<int>);

	// This private method that is responsible
	// for solving the problem.
	// disksCount : how many disks
	// source : the index of the source
	// destination : the index of the destination
	// intermediate : the index of the intermediate
	void Hanoi(int disksCount, int source, int destination, int intermediate);

	// As its name implies - moves a disk from one tower to another one
	void MoveDiskFromTo(int source, int destination);

	// Returns element in a given
	// list at a specified index
	int GetListElement(list<int>, int);

	// Convert the place of the disk index
	// to its corresponding string
	string PlaceIntToString(int);
};