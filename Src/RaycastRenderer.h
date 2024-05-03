#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Vector2.h"
#include <Vector>
#include "Texture.h"

struct RaycastResult {
	Vector2<float> HitPos;
	int Distance;
	int WallNumber;
	bool UseY;
};



class RaycastRenderer 
{
	Map* M;
	Player* P;
	std::vector<sf::RectangleShape> Lines;
	float ScanLines;
	Texture Tex;
	int MidPoint;
	Vector2<float> Scr_Size;
	RaycastResult Raycast(float X, float Y, float A);
public:
	float Fov;
	void Render(sf::RenderWindow* Screen);
	void InitEngine(Map *Ma,Player *Plr, Vector2<float> ScreenSize,int F);
};

