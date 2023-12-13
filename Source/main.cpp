#include <SFML/Graphics.hpp>
#include "../Headers/Config.h"
#include "../Headers/UI.h"
#include "../Headers/Events.h"
#include "../Headers/EditBox.h"
#include "../Headers/Gui.h"
#include "../Headers/PluginManager.h"

// #define DEBUG

int main(int argc, const char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ps", sf::Style::None);
    
    plugin::App app = App();

    HostApp hostApp;

    PluginManager pluginManager = PluginManager(argc - 1); 
    for (size_t curPlug = 1; curPlug < argc; curPlug++)
        pluginManager.loadPlugin(argv[curPlug], &app);

    ToolManager toolManager = ToolManager();
    toolManager.setColor({255, 0, 0, 255});
    toolManager.setTool(new Circle);
    
    FilterManager filterManager = FilterManager();
    filterManager.setFilter(new ReverseFilter);

    RenderTarget rt = RenderTarget(Vect(0, 0), Vect(WINDOW_WIDTH, WINDOW_HEIGHT));

    EventManager eventManager = {};

    hostApp.eventManager  = &eventManager;
    hostApp.filterManager = &filterManager;
    hostApp.toolManager   = &toolManager;
    hostApp.pluginManager = &pluginManager;

    Window *mainWindow = orginiseMainScreen(&window, &hostApp);
    clipRegions(mainWindow);

    eventManager.registerObject(mainWindow);
    eventManager.registerObject(hostApp.modalWindow);

    Gui gui(&rt, mainWindow);

    app.root = &gui;
    app.event_manager  = &eventManager;

    while (window.isOpen())
    {
        plugin::KeyboardContext context;

        sf::Event event;
        while (window.pollEvent(event))
        {
            // FILE *logFile = fopen("logFile.txt", "a");
            // fprintf(logFile, "%d -> RegionSetSize at %s at %s(%d)\n", mainWindow->getRegionSet()->getSize(), __PRETTY_FUNCTION__, __FILE__, __LINE__); 
            // fclose(logFile);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
                eventManager.executeEvent(EventManager::Events::MouseLeftClick, &window, context);

            if (event.type == sf::Event::MouseMoved)
                eventManager.executeEvent(EventManager::Events::MouseMove, &window, context);

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                eventManager.executeEvent(EventManager::Events::MouseLeftRelease, &window, context);
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LShift)
                context.shift = true;

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LShift)
                context.shift = false;

            if (event.type == sf::Event::KeyPressed && event.key.code != sf::Keyboard::LShift) {
                context.key = plugin::Key(event.key.code);
                eventManager.executeEvent(EventManager::Events::KeyPressed, &window, context);
            }

            if (event.type == sf::Event::KeyReleased && event.key.code != sf::Keyboard::LShift) {
                context.key = plugin::Key(event.key.code);
                eventManager.executeEvent(EventManager::Events::KeyReleased, &window, context);
            }

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