#pragma once
#include "Vector2.h"
#include <SFML\Graphics.hpp>

class Mode7
{
	Vector2<unsigned int> Screen_Res;
	Vector2<unsigned int> H_Screen_Res;
	Vector2<unsigned int> ImgSize;
	int Focal = 25;
	int Scale = 100;
	sf::Image Source;
	sf::Texture Tranformed;
	sf::RectangleShape Canvas;
public:
	void Setup(const char* FilePath, Vector2<unsigned int> ScreenRes, int Sc);
	void Update(Vector2<unsigned int> Pos, int A);
	void Draw(sf::RenderTarget &Screen);
};

