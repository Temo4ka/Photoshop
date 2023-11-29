#pragma once

#include <windows.h>
#include "List.h"
#include "plugin.h"

typedef plugin::Plugin* (*GetInstance_type) (plugin::App *);


struct PluginManager {
    size_t pluginNum;

    ListHead<plugin::Plugin> plugins;

    PluginManager(size_t pluginNum):
             pluginNum (pluginNum)
    {}

    int loadPlugin(const char *name, plugin::App *app);

    ~PluginManager() {}
};