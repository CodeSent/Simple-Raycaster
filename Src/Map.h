#pragma once
#include "Vector2.h"
#define MapSize 10
#define _ 0

class Map
{
	int MAP[MapSize][MapSize] =
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,_,_,_,_,1,_,_,_,1},
		{1,_,1,2,_,1,_,1,_,1},
		{1,_,1,_,_,_,_,1,_,1},
		{1,_,_,_,_,1,_,2,_,1},
		{1,_,1,1,1,1,_,1,_,1},
		{1,_,_,_,_,_,_,1,_,1},
		{1,_,1,1,1,_,1,1,_,1},
		{1,_,_,1,_,_,_,_,_,1},
		{1,1,1,1,1,1,1,1,1,1}
	};
	
	int XSize, YSize;
public:
	int CellSize;
	int MapSizeF;
	const char* Floor = "Textures/PngFloor.png";
	int GetMapPointValue(int x, int y);
	void Init(int ScreenW,int ScreenH);
};

