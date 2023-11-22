#include "../Headers/Filter.h"

void ReverseFilter::apply(plugin::RenderTargetI *data) {
    catchNullptr(rt, /*Error*/);

    RenderTarget* target = data;

    sf::RenderTexture *rt = getWindow();

    sf::Texture texture = rt -> getTexture();

    sf::Image image = texture.copyToImage();

    sf::Vector2u size = image.getSize();

    for (int y = 0; y < size.y; y++)
        for (int x = 0; x < size.x; x++) {
            sf::Color curColor = image.getPixel(x, y);

            image.setPixel(x, y, sf::Color(255 - curColor.r, 255 - curColor.g, 255 - curColor.b));
        }

    texture.loadFromImage(image);
    
    sf::Sprite sprite;
    sprite.setTexture(texture);

    rt -> draw(sprite);

    return;
}

void FilterManager::applyFilter() {
    lastFilter -> apply(curRenderTarget);

    return;
}