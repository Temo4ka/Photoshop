#include "Vect.h"
#include "List.h"
#include <SFML/Graphics.hpp>
#include <stdint.h>

class RegionSet;

class Region {
    Vect pos;
    Vect size;

    public:
        Region(Vect pos, Vect size):
                pos (pos),
                          size (size)
        {
        // FILE *logFile = fopen("logFile.txt", "a");
        // fprintf(logFile, "Pos(%lg, %lg) - Size(%lg, %lg) NEW REGION at %s at %s(%d)\n", pos.x, pos.y, size.x, size.y, __PRETTY_FUNCTION__, __FILE__, __LINE__); 
        // fclose(logFile);
        }
        
        Vect getPos () { return this -> pos ; }
        Vect getSize() { return this -> size; }

        RegionSet* crossRegion(Region &r);
        RegionSet*  subRegion (Region &r);
        RegionSet* unionRegion(Region &r);
};

class RegionSet {
    ListHead<Region> *set;
    size_t size;

    public:
        RegionSet():
        size(0),
        set(new ListHead<Region>())
        {}

        size_t getSize() { return this -> size; }

        int addRegion(Region *region);

        RegionSet* crossRegions(RegionSet *r);
        RegionSet*   subRegions(RegionSet *r);
        
          void     unionRegions(RegionSet *r);
    
        ListHead<Region> *getHead() { return set; }

        void dump(sf::RenderWindow *window);
        
        ~RegionSet() {
            // MESSAGE("Size -> %d", size);

            // ListNode<Region> *node = set -> getHead();
            // for (int i = 0; i < size; i++) {
            //     Vect pos  = node ->getObject()->getPos ();
            //     Vect sz = node ->getObject()->getSize();

            //     MESSAGE("POSITION(%lg, %lg) <-> SIZE(%lg, %lg)", pos.x, pos.y, sz.x, sz.y);

            //     node = node -> getNext();
            // }
            // MESSAGE("%p is dead", this);
        }
};