#include "../Headers/Scrollbar.h"

ScrollbarH::ScrollbarH(Canvas *canvas, Vect &pos, Vect &size, sf::Texture *texture, const signed texW, const signed texH,
                                                                                                sf::Sprite *sprite, Widget *parent = nullptr):
Widget(pos, size, texture, texW, texH, sprite, parent),
canvas (canvas)
{
    buttonTexture.loadFromFile(SCROLLBAR_BUTTON_FILENAME);
    Vect butSize = Vect(SCROLLBARH_BUT_WIDTH, SCROLLBARH_BUT_HEIGHT);
}
