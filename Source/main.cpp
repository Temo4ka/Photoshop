#include <SFML/Graphics.hpp>
#include "../Headers/Config.h"
#include "../Headers/UI.h"
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ps", sf::Style::None);
    Window *mainWindow = orginiseMainScreen(&window);

    RenderTarget rt = RenderTarget(&window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                Vect pos = Vect(mousePos.x, mousePos.y);
                mainWindow -> onMouseClick(pos);
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                Vect pos = Vect(mousePos.x, mousePos.y);
                mainWindow -> onMouseMove(pos);
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                Vect pos = Vect(mousePos.x, mousePos.y);
                mainWindow -> onMouseReleased(pos);
            }

        }

        window.clear();

        mainWindow -> draw(&rt);
        
        window.display();
    }

    return 0;
}