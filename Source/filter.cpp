#include "../Headers/Filter.h"
#include "../Headers/RenderTarget.h"

void ReverseFilter::apply(plugin::RenderTargetI *data) {
    catchNullptr(data, /*Error*/);

    plugin::Texture *texture = data -> getTexture();

    enum Color {
        red = 0,
        green,
        blue,
        alpha,
    }

    for (int y = 0; y < size.y; y++)
        for (int x = 0; x < size.x; x++) {
            int curX = x * 4;

            texture -> data[curX +  red ] = 255 - texture -> data[curX +  red ];
            texture -> data[curX + green] = 255 - texture -> data[curX + green];
            texture -> data[curX + blue ] = 255 - texture -> data[curX + blue ];
        }

    data -> drawTexture(Vec2(-1, -1), Vec2(texture -> size.x, texture -> size.y), texture);

    return;
}

void FilterManager::applyFilter() {
    lastFilter -> apply(curRenderTarget);

    return;
}