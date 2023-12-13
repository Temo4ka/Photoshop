#include "../Headers/Gui.h"

Vec2 Gui::getSize() {
    Vect size = rt -> getSize();

    return Vec2(size.x, size.y);
}


void Gui::createWidgetI(PluginWidgetI* widget) {

    return;
}

Plugin* Gui::queryPlugin(uint64_t id) {

    return nullptr;
}

Texture* Gui::loadTextureFromFile(const char *filename) {

    return nullptr;
}