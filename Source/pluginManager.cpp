#include "../Headers/PluginManager.h"

using namespace plugin;

int PluginManager::loadPlugin(const char *name, App *app) {
    HMODULE hComponent = LoadLibrary(name);
    catchNullptr(hComponent, EXIT_FAILURE);

    GetInstance_type GetInstance = (GetInstance_type) GetProcAddress(hComponent, "getInstance");
    catchNullptr(GetInstance, EXIT_FAILURE);

    Plugin *plug = GetInstance(app);
    plugins.pushBack(plug);

    return EXIT_SUCCESS;
}