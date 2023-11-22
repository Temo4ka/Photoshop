#pragma once

#include <SFML/Graphics.hpp>
#include "List.h"
#include "plugin.h"

class Filter : plugin::FilterI {
    size_t paramsNum;

    Array<const char *> paramNames;
    Array<   double   >   params  ;

    public:
        Filter() :
        paramsNum(0)
        {}

        virtual void apply(plugin::RenderTargetI *data) = 0;

        Array<const char *> getParamNames()  { return paramNames; }
        Array<  double    >    getParams()   { return   params  ; }

        void setParams(Array<double> params) { this -> params = params; }


};

struct FilterManager : plugin::FilterManagerI {
    plugin::FilterI *lastFilter;

    plugin::RenderTargetI *curRenderTarget;

    bool active;

    FilterManager():
    lastFilter(nullptr),
      active  ( false )
    {}  

    void applyFilter();

    void setFilter(plugin::FilterI *filter) { lastFilter = filter; }

    void setRenderTarget(plugin::RenderTargetI *target) { curRenderTarget = target; }

};

class ReverseFilter : public Filter {
    public:
        ReverseFilter(): Filter() {}

        void apply(plugin::RenderTargetI *data);
};