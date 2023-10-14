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

    if (a.y + sizeA.y < b.y || b.y + sizeB.y < a.y ||
        a.x + sizeA.x < b.x || b.x + sizeB.x < a.x) {
        set->addRegion(this);    
        return set;
    }

    if (a.y < b.y) {
        set->addRegion(new Region(a, Vect(sizeA.x, b.y - a.y)));
    }

    if (a.x < b.x) {
        set->addRegion(new Region(Vect(a.x, max(b.y, a.y)),
                               Vect(b.x - a.x, min(a.y + sizeA.y, b.y + sizeB.y) - max(a.y, b.y))));
    }

    if (b.y + sizeB.y < sizeA.y + a.y) {
        set->addRegion(new Region(Vect(a.x, b.y + sizeB.y), Vect(sizeA.x, a.y + sizeA.y - b.y - sizeB.y)));
    }

    if (b.x + sizeB.x < sizeA.x + a.x) {
        set->addRegion(new Region(Vect(b.x + sizeB.x, max(b.y, a.y)),
                               Vect(sizeA.x + a.x - b.x - sizeB.x, min(a.y + sizeA.y, b.y + sizeB.y) - max(a.y, b.y))));
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

int RegionSet::addRegion(Region *region) {
    if (this -> size == MAX_SIZE_REGIONS) return EXIT_FAILURE;

    set -> pushBack(region);
    (this -> size)++;

    return EXIT_SUCCESS;
}

void RegionSet::unionRegions(RegionSet *that) {
    ListNode<Region> *cur = (that -> getHead())->getHead();

    for (int i = 0; i < that->size; i++) { 
        addRegion(cur -> getObject());
        cur = cur -> getNext();

    }
    
    return;
}

RegionSet* RegionSet::subRegions(RegionSet *that) {
    RegionSet *newSet = new RegionSet();

    ListNode<Region> *curThis = (this->set)->getHead();
    for (int i = 0; i < size; i++) {

        ListNode<Region> *curThat = (that->set)->getHead();
        for (int j = 0; j < that -> getSize(); j++) {
            newSet -> unionRegions( ((curThis->getObject())->subRegion( *(curThat -> getObject()) )) );
             Vect sz  = curThat->getObject()->getSize();
            Vect pos = curThat->getObject()->getPos ();   

            FILE *logFile = fopen("logFile.txt", "a");
            fprintf(logFile, "Pos(%lg, %lg) - Size(%lg, %lg) = Size at %s at %s(%d)\n", pos.x, pos.y, sz.x, sz.y, __PRETTY_FUNCTION__, __FILE__, __LINE__); 
            fclose(logFile);
        
            curThat = curThat->getNext();
        }
        curThis = curThis -> getNext();
    }

    return newSet;
}

RegionSet *RegionSet::crossRegions(RegionSet *that) {
    RegionSet *newSet =  new RegionSet();

    ListNode<Region> *curThis = (this->set)->getHead();
    for (int i = 0; i < size; i++) {

        ListNode<Region> *curThat = (that->set)->getHead();
        for (int j = 0; j < that -> getSize(); j++) {
            newSet -> unionRegions( ((curThis->getObject())->crossRegion( *(curThat -> getObject()) )) );
            curThat = curThat->getNext();
        }
        curThis -> getNext();
    }

    return newSet;
}

void RegionSet::dump(sf::RenderWindow *window) {
    int k = rand() % 255 + 10;

    ListNode<Region> *cur = set->getHead();
    for (int i = 0; i < size; i++) {
        Vect sz  = cur->getObject()->getSize();
        Vect pos = cur->getObject()->getPos ();   

        // FILE *logFile = fopen("logFile.txt", "a");
        // fprintf(logFile, "Pos(%lg, %lg) - Size(%lg, %lg) = Size at %s at %s(%d)\n", pos.x, pos.y, sz.x, sz.y, __PRETTY_FUNCTION__, __FILE__, __LINE__); 
        // fclose(logFile);
    
        sf::RectangleShape rect(sf::Vector2f(sz.x, sz.y));
        rect.setPosition(sf::Vector2f(pos.x, pos.y));
        rect.setFillColor(sf::Color(k, 255 - k, 125 + k % 255, 70));

        window -> draw(rect);

        cur = cur -> getNext();
    }
    // FILE *logFile = fopen("logFile.txt", "a");                                                                                 
    // fprintf(logFile, "----------------------------------------\n");                   
    // fclose(logFile);

    return;
}

double max(double a, double b) {
    return (a > b)? a : b;
}

double min(double a, double b) {
    return (a < b)? a : b;
}