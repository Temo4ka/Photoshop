#include <SFML/Graphics.hpp>
#include "../Headers/Config.h"
#include "../Headers/UI.h"
#include "../Headers/Events.h"
#include "../Headers/EditBox.h"

// #define DEBUG
 
int main()
{
    plugin::App app;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ps", sf::Style::None);
    
    Window *mainWindow = orginiseMainScreen(&window);

    RenderTarget rt = RenderTarget(Vect(0, 0), Vect(WINDOW_WIDTH, WINDOW_HEIGHT));

    clipRegions(mainWindow);

    EventManager eventManager = {};
    eventManager.registerObject(mainWindow);

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

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
                eventManager.executeEvent(EventManager::Events::MouseLeftClick, &window);

            if (event.type == sf::Event::MouseMoved)
                eventManager.executeEvent(EventManager::Events::MouseMove, &window);

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                eventManager.executeEvent(EventManager::Events::MouseLeftRelease, &window);
            

        }
    window.clear();

#ifdef DEBUG
        mainWindow -> dumpRegions(&window);
        // _sleep(2000);
#else
        // MESSAGE("Before DRAW");
        mainWindow -> draw(&rt);
        
        rt.display();

        sf::Sprite sprite(rt.getWindow()->getTexture());

        sf::Vector2f scale = sprite.getScale();
        
        window.draw(sprite);
        // MESSAGE("After DRAW");
#endif
  
        window.display();
    }

    return 0;
}