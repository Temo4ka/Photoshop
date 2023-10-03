#include "../Headers/Config.h"
#include "../Headers/ClippingRegion.h"
#include <iomanip>
#include <cmath>

double max(double a, double b);
double min(double a, double b);

RegionSet* Region::subRegion(Region &r) {
    Vect   a   = this->pos ;
    Vect sizeA = this->size;

    Vect   b   = r.getPos ();
    Vect sizeB = r.getSize();

    RegionSet *set = new RegionSet;
    Region *newRegion = nullptr;

    if (a.y + sizeA.y < b.y || b.y + sizeB.y < a.y ||
        a.x + sizeA.x < b.x || b.x + sizeB.x < a.x) {
        newRegion = this;
        set->addRegion(newRegion);    
    }

    if (a.y < b.y) {
        newRegion = new Region(a, Vect(sizeA.x, b.y - a.y));
        set->addRegion(newRegion);
    }

    if (a.x < b.x) {
        newRegion = new Region(Vect(a.x, max(b.y, a.y)),
                               Vect(b.x - a.x, min(a.y + sizeA.y, b.y + sizeB.y) - max(a.y, b.y)));
        set->addRegion(newRegion);
    }

    if (b.y + sizeB.y < sizeA.y + a.y) {
        newRegion = new Region(Vect(a.x, b.y + sizeB.y), Vect(sizeA.x, a.y + sizeA.y - b.y - sizeB.y));
        set->addRegion(newRegion);
    }

    if (b.x + sizeB.x < sizeA.x + a.x) {
        newRegion = new Region(Vect(b.x + sizeB.x, max(b.y, a.y)),
                               Vect(sizeA.x + a.x - b.x - sizeB.x, min(a.y + sizeA.y, b.y + sizeB.y) - max(a.y, b.y)));
        set->addRegion(newRegion);
    }

    return set;
}

RegionSet* Region::crossRegion(Region &r) {
    Vect   a   = this->pos ;
    Vect sizeA = this->size;

    Vect   b   = r.getPos ();
    Vect sizeB = r.getSize();

    if (a.y + sizeA.y < b.y || b.y + sizeB.y < a.y ||
        a.x + sizeA.x < b.x || b.x + sizeB.x < a.x)
        return nullptr;

    RegionSet *set = new RegionSet;
    Region *newRegion = new Region(Vect(max(a.x, b.x), max(a.y, b.y)),
                                   Vect(min(a.x + sizeA.x, b.x + sizeB.x) - max(a.x, b.x), min(a.y + sizeA.y, b.y + sizeB.y) - max(a.y, b.y)));
    set->addRegion(newRegion);

    return set;
}

RegionSet::RegionSet() {
    this -> set  = new Region*[MAX_SIZE_REGIONS];
    this -> size = 0;
}

int RegionSet::addRegion(Region *region) {
    if (this -> size == MAX_SIZE_REGIONS) return EXIT_FAILURE;

    this -> set[this -> size] = region;
    (this -> size)++;

    return EXIT_SUCCESS;
}

void RegionSet::unionRegions(RegionSet &r) {
    for (int i = 0; i < this->size; i++)
        addRegion(r.set[i]);
    
    return;
}

RegionSet* RegionSet::subRegions(RegionSet &r) {
    RegionSet *set = new RegionSet;

    for (int i = 0; i < size; i++) {
        Region *cur = this->set[i];

        for (int j = 0; j < r.getSize(); j++) {
            set -> unionRegions( *(cur->subRegion( *(r.set[j]) )) );
        }
    }

    return set;
}

RegionSet* RegionSet::crossRegions(RegionSet &r) {
    RegionSet *set = new RegionSet;

    for (int i = 0; i < size; i++) {
        Region *cur = this->set[i];

        for (int j = 0; j < r.getSize(); j++) {
            set -> unionRegions( *(cur->crossRegion( *(r.set[j]) )) );
        }
    }

    return set;
}

double max(double a, double b) {
    return (a > b)? a : b;
}

double min(double a, double b) {
    return (a < b)? a : b;
}