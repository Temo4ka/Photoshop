#pragma once

#include <SFML/Graphics.hpp>
#include "List.h"

class Filter {
    size_t paramsNum;
    ListHead<const char*> paramsNames;
    ListHead<  double   >   params   ;

    public:
        Filter() :
        paramsNames(ListHead<const char *> ()),
        params(ListHead<double> ()),
        paramsNum(0)
        {}

        virtual void apply(sf::RenderTexture *rt) = 0;

        ListHead<const char *> getParamsNames() { return paramsNames; } 
};

class FilterManager {
    Filter *lastFilter; 

    bool active;

    public:

        FilterManager():
        lastFilter(nullptr),
          active  ( false )
        {}

        void setFilter(Filter *filter) { lastFilter = filter; }
};

class ReverseFilter : public Filter {
    public:
        ReverseFilter(): Filter() {}

        void apply(sf::RenderTexture *rt);
};