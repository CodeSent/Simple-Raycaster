#include "Player.h"
#include <iostream>
#include <cmath>

#define RAD(A)  (3.14159265359/180)* A



void Player::InitPlayer(int X, int Y, int Angle, Map *M)
{
	this->X = X;
	this->Y = Y;
	this->Angle;
	Ma = M;
}

void Player::Move(int steps, int AngleOffset)
{
	int XM, YM;
	XM = std::cos(RAD(this->Angle + AngleOffset)) * steps;
	YM = std::sin(RAD(this->Angle + AngleOffset)) * steps;
	int CS = (*Ma).CellSize;
	if ((*Ma).GetMapPointValue(int(X / CS), int((YM* Size + Y) / CS)) == 0) {
		Y += YM;
	}
	if ((*Ma).GetMapPointValue(int((XM * Size + X) / CS), int(Y / CS)) == 0) {
		X += XM;
	}
	//std::cout << this->Angle + AngleOffset << "\n";
}


void Player::SetAngle(int A)
{
	this->Angle += A;
	if (this->Angle < 0) {
		this->Angle += 360;
	}
	//std::cout << this->Angle << "\n";
}
