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
        }

        window.clear();

        mainWindow -> draw(&rt);
        
        window.display();
    }

    return 0;
}