#include "../Headers/Filter.h"
#include "../Headers/RenderTarget.h"

void FilterManager::setFilter(plugin::FilterI *filter) {
    catchNullptr(filter, );
    
    if (this -> lastFilter != nullptr) delete this -> lastFilter;
    this -> lastFilter = filter;

    return;
}

void ReverseFilter::apply(plugin::RenderTargetI *data) {
    catchNullptr(data, /*Error*/);

    plugin::Texture *texture = data -> getTexture();

    int h = texture->height;
    int w = texture->width;

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            texture -> pixels[y * w + x].r = 255 - texture -> pixels[y * w + x].r;
            texture -> pixels[y * w + x].g = 255 - texture -> pixels[y * w + x].g;
            texture -> pixels[y * w + x].b = 255 - texture -> pixels[y * w + x].b;
        }

    data -> drawTexture(Vec2(0, 0), Vec2(w, h), texture);

    return;
}

void FilterManager::applyFilter() {
    lastFilter -> apply(curRenderTarget);

    return;
}