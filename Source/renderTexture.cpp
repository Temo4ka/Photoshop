#include "../Headers/RenderTarget.h"
#include "../Headers/Config.h"

sf::Color translateColor(Color color);

void RenderTarget::setPixel(Vec2 pos, Color color) {
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
    sf::RectangleShape rectangle(sf::Vector2f(size.x + pos.x, size.y + pos.y));
    rectangle.setPosition(pos.x, pos.y);
    rectangle.setFillColor(translateColor(color));
    window -> draw(rectangle);
}

void RenderTarget::drawEllipse(Vec2 pos, Vec2 size, Color color) {
    float radius = std::max(size.x, size.y);

    sf::CircleShape circle(radius);
    circle.setPosition(pos.x, pos.y);
    circle.setFillColor(translateColor(color));
    circle.setScale(size.x / radius, size.y / radius);
    window -> draw(circle);
}

void RenderTarget::drawTexture(Vec2 pos, Vec2 size, const Texture *texture) {
    catchNullptr(texture, );

    sf::Image image;
    image.create(size.x, size.y, texture.data);

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
    Texture *texture = new Texture;

    texture->width  = size.x;
    texture->height = size.y;

    sf::Image image = window.getTexture().copyToImage();

    uint8_t *pixels = image.getPixelsPtr();
    
    texture->pixels = (uint8_t *) calloc(size.x * size.y * 4, sizeof(uint8_t));

    memcpy(texture -> pixels, pixels, size.x * size.y * 4 * sizeof(uint8_t));

    return texture;
}