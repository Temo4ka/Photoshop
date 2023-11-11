#include "../Headers/Filter.h"

void ReverseFilter::apply(sf::RenderTexture *rt) {
    catchNullptr(rt, /*Error*/);

    sf::Texture texture = rt -> getTexture();

    sf::Image image = texture.copyToImage();

    sf::Vect2u size = image.getSize();

    for (int y = 0; y < size.y; y++)
        for (int x = 0; x < size.x; x++) {
            sf::Color curColor = image.getPixel(x, y);

            image.setPixel(sf::Color(255 - curColor.r, 255 - curColor.g, 255 - curColor.b));
        }

    texture.loadFromImage(image);
    
    sf::Sprite sprite;
    sprite.setTexture(texture);

    rt -> draw(sprite);

    return;
}