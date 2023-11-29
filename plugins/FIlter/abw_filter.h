#include "../../Headers/plugin.h"
#include "../../Headers/DSL.h"

using namespace plugin;

class AutoBalanceWhite_filter : public FilterI {
    Array<const char *> paramNames;
    Array<double>        params  ; 

    public:

        AutoBalanceWhite_filter();

        void apply(RenderTargetI *data);
        
        Array<const char *> getParamNames() { return paramNames; }
        Array<double> getParams() { return params; }

        void setParams(Array<double> params) { this -> params = params; }
        
        ~AutoBalanceWhite_filter() {}
};

class AutoBalanceWhite_plugin : public Plugin {
    AutoBalanceWhite_filter *filter;

    public:

         AutoBalanceWhite_plugin() {
            id = 0x1EDA;
            name = "ABW";
            type = InterfaceType::Filter;
            filter = new AutoBalanceWhite_filter;
        }

        Interface *getInterface() { return filter; }

        ~AutoBalanceWhite_plugin() { delete filter; }

};