#include "Texture.h"

void Texture::LoadTexture(const char* FP)
{
	if (TextureSource.loadFromFile(FP)) {
		FilePath = FP;
		sf::Vector2u S = TextureSource.getSize();
		TextureSize = { int(S.x),int(S.y) };
	}
}
