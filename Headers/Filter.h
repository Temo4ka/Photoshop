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

        void apply(sf::RenderTexture *rt);

        ListHead<const char *> getParamsNames() { return paramsNames; } 
};
