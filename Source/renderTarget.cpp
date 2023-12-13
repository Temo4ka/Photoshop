#include "../Headers/RenderTarget.h"
#include "../Headers/Config.h"
#include "../Headers/DSL.h"

void RenderTarget::setPixel(Vec2 pos, Color color) {
    display();

    sf::Texture texture = window -> getTexture();

    sf::Image image = texture.copyToImage();

    image.setPixel(pos.x, pos.y, translateColor(color));

    texture.loadFromImage(image);
    
    sf::Sprite sprite;
    sprite.setTexture(texture);

    window -> clear();
    window -> draw(sprite);
}

void RenderTarget::drawLine(Vec2 point1, Vec2 point2, Color color) {
    sf::Vertex vertices[] = {
        sf::Vertex(sf::Vector2f(point1.x, point1.y), translateColor(color)),
        sf::Vertex(sf::Vector2f(point2.x, point2.y), translateColor(color))
    };
    window -> draw(vertices, 2, sf::Lines);
}

void RenderTarget::drawRect(Vec2 pos, Vec2 size, Color color) {
    sf::RectangleShape rectangle(sf::Vector2f(size.x, size.y));
    rectangle.setPosition(pos.x, pos.y);
    rectangle.setFillColor(translateColor(color));
    window -> draw(rectangle);
}

void RenderTarget::drawEllipse(Vec2 pos, Vec2 size, Color color) {
    float radius = std::max(size.x, size.y) / 2;

    sf::CircleShape circle(radius);
    circle.setPosition(pos.x, pos.y);
    circle.setFillColor(translateColor(color));
    circle.setScale(size.x / radius, size.y / radius);
    window -> draw(circle);
}

void RenderTarget::drawTexture(Vec2 pos, Vec2 size, const Texture *texture) {
    catchNullptr(texture, /*nothing*/);

    sf::Image image;
    image.create(size.x, size.y, (uint8_t *) texture->pixels);

    sf::Texture sfmlTexture;
    sfmlTexture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(sfmlTexture);

    if (pos.x == -1 && pos.y == -1)
        sprite.setPosition(POSITION.x, POSITION.y);
    else
        sprite.setPosition(pos.x, pos.y);

    window -> draw(sprite);
}

void RenderTarget::drawText(Vec2 pos, const char *content, uint16_t char_size, Color color) {
    catchNullptr(content, );

    sf::Font font;
    font.loadFromFile(ARIAL_FONT_FILE_NAME);

    sf::Text text = sf::Text(content, font);
    text.setPosition(pos.x, pos.y);
    text.setCharacterSize(char_size);

    window -> draw(text);
}

sf::Color translateColor(Color color) {
    return sf::Color(color.r, color.g, color.b, color.a);
}

Texture* RenderTarget::getTexture() {
    display();

    Texture *texture = new Texture;

    texture->width  = size.x;
    texture->height = size.y;

    sf::Image image = window->getTexture().copyToImage();

    const uint8_t *pixels = image.getPixelsPtr();
    
    texture->pixels = (plugin::Color *) calloc(size.x * size.y, sizeof(plugin::Color));

    memcpy(texture -> pixels, pixels, size.x * size.y * 4 * sizeof(uint8_t));

    return texture;
}

void RenderTarget::setTexture(Texture *texture) {
    display();

    sf::Image image;
    image.create(texture -> width, texture -> height, (const uint8_t*) texture -> pixels);

    sf::Texture tex;
    tex.loadFromImage(image);

    sf::Sprite sprite(tex);

    window -> draw(sprite);

    return;
}