#pragma once
#include "Map.h"

struct Player
{;
    Map* Ma;
	int X, Y , Angle;
	float Size = 1.25;
	void InitPlayer(int X, int Y, int Angle, Map *M);
	void Move(int steps,int AngleOffset);
	void SetAngle(int A);
};

