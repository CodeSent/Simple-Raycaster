#pragma once
#include "Vector2.h"
#include <SFML/Graphics.hpp>

struct Texture
{
	Vector2<int> TextureSize;
	sf::Texture TextureSource;
	const char* FilePath;
	void LoadTexture(const char* FP);
};

