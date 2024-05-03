#pragma once
#include "RaycastRenderer.h"
#include "Mode7.h"

class EngineWindow
{
	sf::RenderWindow *Window;
	bool Running = true;
public:
	Map Ma;
	Mode7 Floor;
	Player Plr;
	RaycastRenderer Engine;
	EngineWindow(int Height , int Width, const char* Title);
	void GameLoop();
	void Terminate();
	void Update();
	void Events();
};

