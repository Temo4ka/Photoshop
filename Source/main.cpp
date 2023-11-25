#include <SFML/Graphics.hpp>
#include "../Headers/Config.h"
#include "../Headers/UI.h"
#include "../Headers/Events.h"
#include "../Headers/EditBox.h"
#include "../Headers/Gui.h"

// #define DEBUG
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ps", sf::Style::None);
    
     ToolManager   toolManager  =  ToolManager ();
    toolManager.setColor({255, 0, 0, 255});
    toolManager.setTool(new Circle);
    
    FilterManager filterManager = FilterManager();
    filterManager.setFilter(new ReverseFilter);

    RenderTarget rt = RenderTarget(Vect(0, 0), Vect(WINDOW_WIDTH, WINDOW_HEIGHT));

    Window *mainWindow = orginiseMainScreen(&window, &filterManager, &toolManager);
    clipRegions(mainWindow);

    EventManager eventManager = {};
    eventManager.registerObject(mainWindow);

    Gui gui(&rt, mainWindow);

    plugin::App app;
    app.root = &gui;
    app.event_manager  = &eventManager;
    app.filter_manager = &filterManager;
    app.tool_manager   = &toolManager;

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