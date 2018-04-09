#include "stdafx.h"
#include "HanoiDrawer.h"


int const HanoiDrawer::SOURCE = 1;
int const HanoiDrawer::INTERMEDIATE = 2;
int const HanoiDrawer::DESTINATION = 3;
int const HanoiDrawer::TOWER_WIDTH = 40;
int const HanoiDrawer::TOWER_HEIGHT = 400;
int const HanoiDrawer::DISK_HEIGHT = 18;
int const HanoiDrawer::INIT_DISKS_COUNT = 3;
int const HanoiDrawer::MAX_DISKS_COUNT = 6;
int const HanoiDrawer::MIN_DISKS_COUNT = 1;
int const HanoiDrawer::DEFAULT_Disks_COUNT = 4;
int const HanoiDrawer::DEFAULT_STEP_TIME = 2000;
int const HanoiDrawer::MAX_STEP_TIME_IN_SECONDS = 6;
int const HanoiDrawer::MIN_STEP_TIME_IN_SECONDS = 1;


HanoiDrawer::HanoiDrawer()
{
	this->hdc = NULL;
	this->iDisksCount = 0;
	this->autoSolve = false;
	this->iMovesCount = 0;
	this->tower1.clear();
	this->tower2.clear();
	this->tower3.clear();
	this->listTower1GUI.clear();
	this->listTower2GUI.clear();
	this->listTower3GUI.clear();
	this->solved = false;
	
}

HanoiDrawer::HanoiDrawer(HDC hdc)
{
	this->hdc = hdc;
	this->iDisksCount = 0;
	this->autoSolve = false;
	this->iMovesCount = 0;
	this->tower1.clear();
	this->tower2.clear();
	this->tower3.clear();
	this->listTower1GUI.clear();
	this->listTower2GUI.clear();
	this->listTower3GUI.clear();
	this->solved = false;
}

HanoiDrawer::HanoiDrawer(HDC hdc, int iPlatesCount)
{
	this->hdc = hdc;
	this->iDisksCount = iPlatesCount;
	this->autoSolve = false;
	this->iMovesCount = 0;
	this->tower1.clear();
	this->tower2.clear();
	this->tower3.clear();
	this->listTower1GUI.clear();
	this->listTower2GUI.clear();
	this->listTower3GUI.clear();
	this->solved = false;
}

HanoiDrawer::HanoiDrawer(HDC hdc=NULL, int platesCount=HanoiDrawer::MIN_DISKS_COUNT, bool autoSolve=false, int movesCount=0)
{
	this->hdc = hdc;
	this->iDisksCount = platesCount;
	this->autoSolve = autoSolve;
	this->iMovesCount = movesCount;
	this->tower1.clear();
	this->tower2.clear();
	this->tower3.clear();
	this->listTower1GUI.clear();
	this->listTower2GUI.clear();
	this->listTower3GUI.clear();
	this->solved = false;
}

void HanoiDrawer::SetTowerCoordinates(Tower stand, int left, int top)
{
	switch (stand)
	{
	case No1 :
		this->arrTowersCoord[0] = HanoiDrawer::PointF(left, top);
		break;
	case No2:
		this->arrTowersCoord[1] = HanoiDrawer::PointF(left, top);
		break;
	case No3:
		this->arrTowersCoord[2] = HanoiDrawer::PointF(left, top);
		break;
	}
}

void HanoiDrawer::DrawTowers()
{
	DrawOneTower(No1);
	DrawOneTower(No2);
	DrawOneTower(No3);
}

void HanoiDrawer::DrawOneTower(Tower stand)
{
	Rectangle(this->hdc, this->arrTowersCoord[stand].x, this->arrTowersCoord[stand].y, this->arrTowersCoord[stand].x + TOWER_WIDTH, this->arrTowersCoord[stand].y + TOWER_HEIGHT);
}

void HanoiDrawer::DrawDisks()
{
	DrawDisks(No1, this->tower1);
	DrawDisks(No2, this->tower2);
	DrawDisks(No3, this->tower3);
}

void HanoiDrawer::DrawDisks(Tower tower, list<int> disks)
{
	DrawDisksInList(No1, this->tower1);
	DrawDisksInList(No2, this->tower2);
	DrawDisksInList(No3, this->tower3);
}

void HanoiDrawer::DrawDisksInList(Tower tower, list<int> listDisks)
{
	list <int>::iterator listDisksIter;
	int i=0, diskNumber;
	double diskWidth;
	const int TEXT_OFFSET_IN_DISK = 4;
	const double DISK_SIZE_ENLARGMENT_CONSTANT = 1.1;

	double x1, y1, x2, y2;
	POINT textCoor;
	RECT rectArea;
	string strPlateLabel;

	// clearing disks in a specific GUI's list
	switch(tower)
	{
	case No1:
		listTower1GUI.clear();
		break;
	case No2:
		listTower2GUI.clear();
		break;
	case No3:
		listTower3GUI.clear();
		break;
	}

	for (listDisksIter = listDisks.begin();listDisksIter!=listDisks.end();listDisksIter++)
	{
		diskNumber = *listDisksIter;
		diskWidth = TOWER_WIDTH/2 * diskNumber * DISK_SIZE_ENLARGMENT_CONSTANT;

		x1 = this->arrTowersCoord[tower].x - diskWidth + TOWER_WIDTH / 2;
		y1 = this->arrTowersCoord[tower].y + TOWER_HEIGHT - DISK_HEIGHT * i - DISK_HEIGHT;
		x2 = this->arrTowersCoord[tower].x + diskWidth + TOWER_WIDTH / 2;
		y2 = this->arrTowersCoord[tower].y + TOWER_HEIGHT - DISK_HEIGHT * i;

		rectArea.left = x1;
		rectArea.top = y1;
		rectArea.right = x2;
		rectArea.bottom = y2;
		textCoor.x = x1 + diskWidth - TEXT_OFFSET_IN_DISK;
		textCoor.y = y1+1;

		strPlateLabel = BuilderExtensions::IntToString(diskNumber);
		DiskGUI* currentDiskGUI = new DiskGUI(strPlateLabel, textCoor, rectArea, x2-x1, y2-y1);

		// adding plate to a specific GUI's list
		switch(tower)
		{
		case No1:
			listTower1GUI.push_back(currentDiskGUI);
			break;
		case No2:
			listTower2GUI.push_back(currentDiskGUI);
			break;
		case No3:
			listTower3GUI.push_back(currentDiskGUI);
			break;
		}

		DrawGUIDisk(strPlateLabel, textCoor, rectArea);
		i++;
	}
}

void HanoiDrawer::DrawGUIDisk(string textString, POINT textCoor, RECT drawingArea)
{
	COLORREF fillColor = RGB(0,0,255) // blue
		, borderColor = RGB(0x00,0x00,0x00);  // black

	SelectObject(this->hdc, CreatePen(PS_SOLID, 1, borderColor));
	SelectObject(this->hdc, CreateSolidBrush(fillColor));

	Ellipse(this->hdc, drawingArea.left, drawingArea.top, drawingArea.right, drawingArea.bottom);

	
	SetBkMode(this->hdc, TRANSPARENT);
	SetTextColor(this->hdc, RGB(0xff,0xff,0x00));

	TextOut(this->hdc, textCoor.x, textCoor.y, textString.c_str(), textString.length());
}

void HanoiDrawer::PopulateDisksList()
{
	this->iMovesCount = 0;
	this->tower1.clear();
	for (int i = this->iDisksCount; i > 0; i--)
	{
		this->tower1.push_back(i);
	}

	this->DrawDisks();
}

void HanoiDrawer::SolveNextStep()
{
	int disksCount
		, source
		, destination
		, intermediate;

	if(listSavedState.size()==0)
	{
		this->Hanoi(this->iDisksCount, HanoiDrawer::SOURCE, HanoiDrawer::DESTINATION, HanoiDrawer::INTERMEDIATE);
	}

	if(listSavedState.size() % 4 != 0 )
	{
		return;
	}

	disksCount = listSavedState.front();
	listSavedState.pop_front();

	source = listSavedState.front();
	listSavedState.pop_front();

	destination = listSavedState.front();
	listSavedState.pop_front();

	intermediate = listSavedState.front();
	listSavedState.pop_front();

	MoveDiskFromTo(source, destination);

	this->iMovesCount++;

	if(iMovesCount == this->GetTotalMovesCount())
	{
		this->solved = true;
	}

	SetDlgItemInt(this->hWnd, this->countContainerResourceId, GetMovesCount(), FALSE);

	SetDlgItemText(this->hWnd, this->fromContainerResourceId, PlaceIntToString(source).c_str() );
	SetDlgItemText(this->hWnd, this->toContainerResourceId, PlaceIntToString(destination).c_str() );
	SetDlgItemText(this->hWnd, this->throughContainerResourceId, PlaceIntToString(intermediate).c_str() );
}

bool HanoiDrawer::IsSolved()
{
	return this->solved;
}

void HanoiDrawer::ReDraw()
{
	DrawTowers();
	DrawDisks();

	Invalidate();
}

void HanoiDrawer::Invalidate()
{
	RECT rect;
	GetClientRect(this->hWnd, &rect);
	InvalidateRect(this->hWnd, &rect, TRUE);
}


void HanoiDrawer::Hanoi(int disksCount, int source, int destination, int intermediate)
{
	if (disksCount == 1)
	{
		listSavedState.push_back(disksCount);
		listSavedState.push_back(source);
		listSavedState.push_back(destination);
		listSavedState.push_back(intermediate);
		return;
	}
	else
	{
		Hanoi(disksCount - 1, source, intermediate, destination);
		Hanoi(1, source, destination, intermediate);
		Hanoi(disksCount - 1, intermediate, destination, source);
		return;
	}
}

int HanoiDrawer::GetMovesCount()
{
	return this->iMovesCount;
}

int HanoiDrawer::GetTotalMovesCount()
{
	return (pow((double)2, (double)this->iDisksCount) - 1);
}

bool HanoiDrawer::GetAutoSolveAction()
{
	return this->autoSolve;
}

int HanoiDrawer::GetDisksCount()
{
	return this->iDisksCount;
}

void HanoiDrawer::SetAutoSolveAction(bool value)
{
	this->autoSolve = value;
}

void HanoiDrawer::SetOwnerInstance(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
}
void HanoiDrawer::SetOwner(HWND hWnd)
{
	this->hWnd = hWnd;
}

void HanoiDrawer::SetHDC(HDC hdc)
{
	this->hdc = hdc;
}

void HanoiDrawer::SetCountContainer(int resourceId)
{
	this->countContainerResourceId = resourceId;
}

void HanoiDrawer::SetFromTextContainer(int resourceId)
{
	this->fromContainerResourceId = resourceId;
}

void HanoiDrawer::SetToTextContainer(int resourceId)
{
	this->toContainerResourceId = resourceId;
}

void HanoiDrawer::SetThroughTextContainer(int resourceId)
{
	this->throughContainerResourceId = resourceId;
}

void HanoiDrawer::SetDisksCount(int platesCount)
{
	if(platesCount>HanoiDrawer::MAX_DISKS_COUNT || platesCount<HanoiDrawer::MIN_DISKS_COUNT)
	{
		platesCount = HanoiDrawer::MAX_DISKS_COUNT;
	}
	this->iDisksCount = platesCount;
	this->PopulateDisksList();
}

void HanoiDrawer::SetStepTime(int seconds)
{
	if(seconds<MAX_STEP_TIME_IN_SECONDS && seconds>MIN_STEP_TIME_IN_SECONDS)
	{
		this->iStepTime = seconds * 1000;
	}
	else
	{
		this->iStepTime = DEFAULT_STEP_TIME;
	}
}

int HanoiDrawer::GetStepTime()
{
	return this->iStepTime;
}

void HanoiDrawer::MoveDiskFromTo(int source, int destination)
{
	int disk;

	switch(source - 1)	// subtract one from first tower to convert
						// it to the number that represents index of the tower
	{
	case 0:
		disk = GetListElement(tower1, tower1.size() - 1);
		break;
	case 1:
		disk = GetListElement(tower2, tower2.size() - 1);
		break;
	case 2:
		disk = GetListElement(tower3, tower3.size() - 1);
		break;
	}

	if(disk != LIST_ELEMENT_NOT_FOUND)
	{
		switch(source - 1)
		{
		case 0:
			tower1.remove(disk);
			break;
		case 1:
			tower2.remove(disk);
			break;
		case 2:
			tower3.remove(disk);
			break;
		}

		switch(destination - 1)
		{
		case 0:
			tower1.push_back(disk);
			break;
		case 1:
			tower2.push_back(disk);
			break;
		case 2:
			tower3.push_back(disk);
			break;
		}
	}

	ReDraw();
}

int HanoiDrawer::GetListElement(list<int> aList, int index)
{
	list<int>::iterator iter = aList.begin();

	for ( int i=0; iter != aList.end(); iter++, i++ )
	{
		if(i==index)
		{
			return *iter;
		}
	}

	return LIST_ELEMENT_NOT_FOUND;
}

string HanoiDrawer::PlaceIntToString(int placeNum)
{
	switch(placeNum)
	{
	case 1:
		return "Source";
		break;
	case 2:
		return "Intermediate";
		break;
	case 3:
		return "Destination";
		break;

	}
	return "";
}

void HanoiDrawer::ShowCurrentStepInfo()
{
	ShowWindow(GetDlgItem(this->hWnd, this->fromContainerResourceId), TRUE);
	ShowWindow(GetDlgItem(this->hWnd, this->toContainerResourceId), TRUE);
	ShowWindow(GetDlgItem(this->hWnd, this->throughContainerResourceId), TRUE);
}

void HanoiDrawer::HideCurrentStepInfo()
{
	ShowWindow(GetDlgItem(this->hWnd, this->fromContainerResourceId), FALSE);
	ShowWindow(GetDlgItem(this->hWnd, this->toContainerResourceId), FALSE);
	ShowWindow(GetDlgItem(this->hWnd, this->throughContainerResourceId), FALSE);
}

HanoiDrawer::~HanoiDrawer()
{
	this->tower1.clear();
	this->tower2.clear();
	this->tower3.clear();
	this->listTower1GUI.clear();
	this->listTower2GUI.clear();
	this->listTower3GUI.clear();
}