#include <SFML/Graphics.hpp>
#include "../Headers/Config.h"
#include "../Headers/UI.h"

// #define DEBUG
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ps", sf::Style::None);
    
    Window *mainWindow = orginiseMainScreen(&window);

    RenderTarget rt = RenderTarget(&window);

    clipRegions(mainWindow);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // FILE *logFile = fopen("logFile.txt", "a");
            // fprintf(logFile, "%d -> RegionSetSize at %s at %s(%d)\n", mainWindow->getRegionSet()->getSize(), __PRETTY_FUNCTION__, __FILE__, __LINE__); 
            // fclose(logFile);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                Vect pos = Vect(mousePos.x, mousePos.y);
                mainWindow -> onMouseClick(pos);
                clipRegions(mainWindow);
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                Vect pos = Vect(mousePos.x, mousePos.y);
                mainWindow -> onMouseMove(pos);
                clipRegions(mainWindow);
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                Vect pos = Vect(mousePos.x, mousePos.y);
                mainWindow -> onMouseReleased(pos);
                clipRegions(mainWindow);
            }

        }
    window.clear();

#ifdef DEBUG
        mainWindow -> dumpRegions(&window);
        _sleep(2000);
#else
        // MESSAGE("Before DRAW");
        mainWindow -> draw(&rt);
        // MESSAGE("After DRAW");
#endif
        
        window.display();
    }

    return 0;
}