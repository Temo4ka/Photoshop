#include "../Headers/Crossbar.h"

CrossbarH::CrossbarH(Canvas *canvas, Vect &pos, Vect &size, sf::Texture *texture, const signed texW, const signed texH,
                                                                                                sf::Sprite *sprite, Widget *parent = nullptr):
Widget(pos, size, texture, texW, texH, sprite, parent),
canvas (canvas)
{
    buttonTexture.loadFromFile(CROSSBAR_BUTTON_FILENAME);
    Vect butSize = Vect(CROSSBARH_BUT_WIDTH, CROSSBARH_BUT_HEIGHT);
}
