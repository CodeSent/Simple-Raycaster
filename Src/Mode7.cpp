#include "Mode7.h"
#include <iostream>
#define Rad (3.14159265359/180)

void Mode7::Setup(const char* FilePath, Vector2<unsigned int> ScreenRes,int Sc)
{
	Source.loadFromFile(FilePath);
	//std::cout << "W: " << ScreenRes.X << ", H: " << ScreenRes.Y << "\n";
	Screen_Res = ScreenRes;
	H_Screen_Res = {Screen_Res.X/2,Screen_Res.Y/2};
	sf::Vector2u S = Source.getSize();
	ImgSize = {S.x,S.y};
	Scale = Sc;
	Canvas = sf::RectangleShape(sf::Vector2f(1.f, 1.f));
	Canvas.setPosition(sf::Vector2f(0.f,0.f));
	Canvas.setSize(sf::Vector2f(Screen_Res.X, Screen_Res.Y));
	Tranformed.create(Screen_Res.X, Screen_Res.Y);

}

void Mode7::Update(Vector2<unsigned int> Pos, int A)
{
	sf::Image PixelBuffer;
	PixelBuffer.create(Screen_Res.X, Screen_Res.Y,sf::Color::Black);
	sf::Vector2u S = PixelBuffer.getSize();
	float cos = std::cos(Rad * A);
	float sin = std::sin(Rad * A);
	for (unsigned int xI = 0; xI < Screen_Res.X; xI++) {
		for (unsigned int yI = H_Screen_Res.Y; yI < Screen_Res.Y; yI++) {

			float x = float(H_Screen_Res.X) - float(xI);
			float y = float(yI)+float(Focal);
			float z = float(yI) - H_Screen_Res.Y +0.001;

			float rx = (x * cos - y * sin);
			float ry = (y * cos + x * sin);

			float px = (rx / z - Pos.Y) * float(Scale);
			float py = (ry / z - Pos.X) * float(Scale);

			Vector2<unsigned int> PixelPos = {
				int(px) % ImgSize.X,
				int(py) % ImgSize.Y
			};
			sf::Color Pixel = Source.getPixel(PixelPos.X,PixelPos.Y);

			float A = std::min<float>(std::max<float>(std::abs(z) / (H_Screen_Res.Y * 3 ), 0), 1);
			Pixel.a *= A;


			PixelBuffer.setPixel(xI, yI, Pixel);
			//PixelBuffer.setPixel(xI, (H_Screen_Res.Y - yI) + 2, Pixel);
		}
	}
	
	Tranformed.loadFromImage(PixelBuffer);
}

void Mode7::Draw(sf::RenderTarget& Screen)
{
	Canvas.setTexture(&Tranformed);
	Screen.draw(Canvas);
}
