#include "RaycastRenderer.h"
#include <iostream>
#include <cmath>

#define RAD(A)  (3.14159265359/180)* A
#define DEG(A)  (180/3.14159265359)* A

#define Ang(I) DEG(std::atan(((I * Scale) - (Scr_Size.X / 2)) / DV))
template <class Type>
Type clamp(Type Number, Type Lower, Type Upper) {
	return std::max<Type>(Lower, std::min<Type>(Number, Upper));
}
sf::RectangleShape Rect;

RaycastResult RaycastRenderer::Raycast(float X, float Y, float A)
{
	float CS = float((*M).CellSize);
	Vector2<float> RayBegin = { X / (CS), Y / (CS) };
	//std::cout << X  << "," << (*M).CellSize<<","<< X / (*M).CellSize << "\n";
	Vector2<float> RayDir = { std::cos(RAD(A)),std::sin(RAD(A)) };
	Vector2<float> RayUnitStep = {
		std::sqrt(1 + (RayDir.Y / RayDir.X) * (RayDir.Y / RayDir.X)),
		std::sqrt(1 + (RayDir.X / RayDir.Y) * (RayDir.X / RayDir.Y))};
	Vector2<int> MapCheck = { int(RayBegin.X),int(RayBegin.Y) };
	Vector2<float> RayLineDistance = { 0,0 };
	Vector2<int> Step = { 0,0 };

	RaycastResult Result;

	if (RayDir.X < 0) {
		Step.X = -1;
		RayLineDistance.X = (RayBegin.X - float(MapCheck.X)) * RayUnitStep.X;
	}
	else {
		Step.X = 1;
		RayLineDistance.X = (float(MapCheck.X + 1) -  RayBegin.X ) * RayUnitStep.X;
	}
	if (RayDir.Y < 0) {
		Step.Y = -1;
		RayLineDistance.Y = (RayBegin.Y - float(MapCheck.Y)) * RayUnitStep.Y;
	}
	else {
		Step.Y = 1;
		RayLineDistance.Y = (float(MapCheck.Y + 1) - RayBegin.Y) * RayUnitStep.Y;
	}



	bool TileReached = false;
	bool UseY = false;
	float AccumilatedDistance = 0.0f;
	float MaxDistance = 10.0f;
	int WallHit = 0;

	while (!TileReached && MaxDistance > AccumilatedDistance) {
		if (RayLineDistance.X < RayLineDistance.Y) {
			// X Line
			UseY = false;
			MapCheck.X += Step.X;
			AccumilatedDistance = RayLineDistance.X;
			RayLineDistance.X += RayUnitStep.X;
		}
		else {
			// Y Line
			UseY = true;
			MapCheck.Y += Step.Y;
			AccumilatedDistance = RayLineDistance.Y;
			RayLineDistance.Y += RayUnitStep.Y;
		}

		if ((*M).GetMapPointValue(MapCheck.X, MapCheck.Y) > 0) {
			WallHit = (*M).GetMapPointValue(MapCheck.X, MapCheck.Y);
			TileReached = true;
		}


	}

	Vector2<float> PointHit = { 0,0 };
	if (TileReached) {
		PointHit = {
			(RayBegin.X + RayDir.X * AccumilatedDistance) * CS,
			(RayBegin.Y + RayDir.Y * AccumilatedDistance) * CS
		};
	}
	//std::cout << PointHit.X<< "Y Axis : " << UseY << ": RayBegin: " << RayBegin.X << " RayDir: " << RayDir.X << " Dist Accumilated: " << AccumilatedDistance << "\n";
	Result.HitPos = PointHit;
	Result.Distance = AccumilatedDistance * CS;
	Result.WallNumber = WallHit;
	Result.UseY = UseY;
	//SDL_SetRenderDrawColor(R, 0, 255, 255, 255);
	//SDL_RenderDrawLineF(R, RayBegin.X* (*M).CellSize, RayBegin.Y * (*M).CellSize, PointHit.X * (*M).CellSize, PointHit.Y * (*M).CellSize);

	return Result;
}

void RaycastRenderer::InitEngine(Map *Ma, Player* Plr, Vector2<float> ScreenSize,int F)
{
	
	M = Ma;
	P = Plr;
	Scr_Size = ScreenSize;
	ScanLines = int(200);
	Fov = F;
	MidPoint = ScreenSize.Y / 2;
	Tex.LoadTexture("Textures/BrickTexture.png");
	for (int I = 0; I < ScanLines; I++) {
		Lines.push_back(sf::RectangleShape(sf::Vector2f(1.f,1.f)));
	}

}

void RaycastRenderer::Render(sf::RenderWindow *Screen)
{
	float X, Y, A;
	X = (*P).X; Y = (*P).Y; A = (*P).Angle;
	int ScreenDis = (Scr_Size.X / 2) / (std::tan(RAD(Fov / 2)));
	float Scale = Scr_Size.X / ScanLines;
	float DV = (Scr_Size.X / 2) / std::tan(RAD(Fov / 2));
	//std::cout << Screen << "\n";
	
	int I = 0;
	for (sf::RectangleShape& RectD: Lines) {
		//std::cout << "Rendering" << "\n";
		float n_Av = Ang(I);
		RaycastResult Result = Raycast(X, Y, A + Ang(I));
		float Dist = Result.Distance * std::cos(RAD(std::abs(n_Av)));
		float Ratio = clamp<float>(1 - ((Dist / (*M).CellSize) / 4), 0, 1);
		if (Ratio > 0) {
			int P_Height = ScreenDis / ((Dist)+0.00001) * 25;
			int XI = (Result.HitPos.X + Result.HitPos.Y) - 1;
			float CS = float((*M).CellSize);
			float PXI = (float((XI % (*M).CellSize)) / CS)* Tex.TextureSize.X;
			float PS = (Tex.TextureSize.X / CS);
			//std::cout << "Rendering" << "\n";
			//std::cout << "X: " << (I * Scale) << ",Y: " << (MidPoint - (P_Height / 2)) << ",W: " << std::floor(Scale) + 1 << ",H: " << P_Height << "\n";

			RectD.setScale(sf::Vector2f(float(std::floor(Scale) + 1), float(P_Height)));
			RectD.setPosition(sf::Vector2f(float(I * Scale), float(MidPoint - (P_Height / 2))));
			RectD.setOutlineThickness(0.f);
			sf::Color C(255 * Ratio, 255 * Ratio, 255 * Ratio, 255);
			RectD.setFillColor(C);
			RectD.setOutlineColor(sf::Color(0,0,0,0));
			RectD.setTexture(&(Tex.TextureSource));
			RectD.setTextureRect(sf::IntRect(PXI, 0, PS, Tex.TextureSize.Y));
			(*Screen).draw(RectD);
		}
		
		I++;
	}
	
}
