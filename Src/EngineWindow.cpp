#include "EngineWindow.h"

#include <iostream>



EngineWindow::EngineWindow(int Height, int Width, const char* Title)
{
    sf::ContextSettings S;
    S.antialiasingLevel = 20;


    sf::RenderWindow  W(sf::VideoMode(Height, Width), Title,sf::Style::Default,S);
    Window = &W;
    
    Ma.Init(Width, Height);
    Plr.InitPlayer(100, 75, 0,&Ma);
    Engine.InitEngine(&Ma, &Plr, { float(Width),float(Height) }, 60);
    Floor.Setup(Ma.Floor, { unsigned int(Width),unsigned int(Height) },Ma.MapSizeF);
    GameLoop();
   

}


void EngineWindow::Terminate()
{
    (*Window).close();
}

void EngineWindow::Update()
{
    //sf::RectangleShape shape(sf::Vector2f(100.f,150.f));
  //  shape.setFillColor(sf::Color::Green);
   // (*Window).draw(shape);
    //std::cout << Window << " , ";
    Floor.Update({ unsigned int(Plr.X),unsigned int(Plr.Y) }, Plr.Angle);
    Floor.Draw((*Window));
    Engine.Render(Window);
}

void EngineWindow::Events()
{
    sf::Event event;
    while ((*Window).pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            Running = false;
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code)
            {
            case(sf::Keyboard::Key::W):
                (Plr).Move(10, 0);
                break;
            case(sf::Keyboard::Key::S):
                (Plr).Move(-10, 0);
                break;
            case(sf::Keyboard::Key::Left):
                (Plr).SetAngle(-10);
                break;
            case(sf::Keyboard::Key::Right):
                (Plr).SetAngle(10);
                break;
            case(sf::Keyboard::Key::A):
                (Plr).SetAngle(-90);
                (Plr).Move(10, 0);
                (Plr).SetAngle(90);
                break;
            case(sf::Keyboard::Key::D):
                (Plr).SetAngle(-90);
                (Plr).Move(-10, 0);
                (Plr).SetAngle(90);
                break;
            default:
                break;
            }
        }
    }
}

void EngineWindow::GameLoop()
{
    while (Running)
    {
        (*Window).clear(sf::Color::Black);

        Events();
        Update();

        (*Window).display();
    }
    Terminate();
}