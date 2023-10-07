#include "Vect.h"
#include <stdint.h>

class RegionSet;

class Region {
    Vect pos;
    Vect size;

    public:
        Region(Vect pos, Vect size):
                pos (pos),
                          size (size)
        {}
        
        Vect getPos () { return this -> pos ; }
        Vect getSize() { return this -> size; }

        RegionSet* crossRegion(Region &r);
        RegionSet*   subRegion(Region &r);
};

class RegionSet {
    Region **set;
    size_t size;

    public:
        RegionSet();

        size_t getSize() { return this -> size; }

        int addRegion(Region *region);

        RegionSet* crossRegions(RegionSet &r);
        RegionSet*   subRegions(RegionSet &r);
        
          void     unionRegions(RegionSet &r);
};