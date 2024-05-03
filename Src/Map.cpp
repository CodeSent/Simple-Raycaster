#include "Map.h"



int Map::GetMapPointValue(int x, int y)
{
	return this->MAP[y][x];
}

void Map::Init(int ScreenW, int ScreenH)
{
	this->XSize = ScreenW;
	this->YSize = ScreenH;
	this->CellSize = 55;
	MapSizeF = CellSize * MapSize;
}
