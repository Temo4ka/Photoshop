#include <windows.h>
#include "List.h"
#include "plugin.h"

typedef plugin::Plugin* (*GetInstance_type) (plugin::App *);

using namespace plugin;

struct PluginManger {
    ListHead<Plugin> plugins;

    PluginManger() {}

    int loadPlugin(const char *name, App *app) {
        HMODULE hComponent = LoadLibrary(name);
        catchNullptr(hComponent, EXIT_FAILURE);

        GetInstance_type GetInstance = (GetInstance_type) GetProcAddress(hComponent, "getInstance");
        catchNullptr(GetInstance, EXIT_FAILURE);

        Plugin *plug = GetInstance(app);
        plugins.pushBack(plug);
    }

    ~PluginManger() {}
};