#include <SFML/Graphics.hpp>
#include "Vect.h"
#include "plugin.h"

using namespace plugin;

class RenderTarget : RenderTargetI {
    Vect pos;
    Vect size;

    sf::RenderTexture *window;

    public:
        RenderTarget(Vect pos, Vect size):
                     pos (pos),
                              size (size)
        {
            window = new sf::RenderTexture;
            window -> create(size.x, size.y);
        }

        sf::RenderTexture *getWindow() { return window; }

        void setPixel(Vec2 pos, Color color);
        void drawLine(Vec2 pos, Vec2 point1, Color color);
        void drawRect(Vec2 pos, Vec2 size, Color color);
        void drawEllipse(Vec2 pos, Vec2 size, Color color);
        void drawTexture(Vec2 pos, Vec2 size, const Texture *texture);
        void drawText(Vec2 pos, const char *content, uint16_t char_size, Color color);

        Texture *getTexture();

        void display() { window -> display(); }

        void clear() { window -> clear(); }
        
        Vect getPosition() { return pos;  }
        Vect   getSize  () { return size; }
};