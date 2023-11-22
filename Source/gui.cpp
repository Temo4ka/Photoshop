#include "../Headers/Gui.h"

Vec2 Gui::getSize() {
    Vect size = rt -> getSize();

    return Vec2(size.x, size.y);
}

RenderTargetI* Gui::getRenderTarget(Vec2 sz, Vec2 pos, Plugin *self) {
    Vect position = Vect(pos.x, pos.y);
    Vect   size   = Vect(sz.x ,  sz.y);

    RenderTaget *newRt = new RenderTarget(pos, size);

    pluginRenders.pushBack(newRt);

    return newRt;
}