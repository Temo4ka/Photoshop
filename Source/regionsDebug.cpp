#include "../Headers/Config.h"
#include "../Headers/DSL.h"
#include "../Headers/ClippingRegion.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CringingRegions.segfault");
    
    RegionSet *a = new RegionSet();
    a->addRegion(new Region(Vect(0, 0), Vect(100, 500)));
    a->addRegion(new Region(Vect(100, 0), Vect(100, 500)));

    RegionSet *b = new RegionSet();
    b->addRegion(new Region(Vect(0, 0), Vect(100, 100)));
    b->addRegion(new Region(Vect(0, 200), Vect(100, 100)));
    b->addRegion(new Region(Vect(0, 100), Vect(100, 100)));
    b->addRegion(new Region(Vect(100, 0), Vect(100, 100)));
    b->addRegion(new Region(Vect(100, 200), Vect(100, 100)));


    a = a->crossRegions(b);

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

        }
        window.clear();
        
        a->dump(&window);
        // b->dump(&window);

        window.display();
        _sleep(2000);
    }

    return 0;
}