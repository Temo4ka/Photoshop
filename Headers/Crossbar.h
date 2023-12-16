#pragma once

#include "Widgets.h"

class CrossbarH : public Widget {
    Canvas *canvas;

    double curYposition;

    sf::Texture *buttonTexture;

    public:

        CrossbarH(Canvas *canvas, Vect &pos, Vect &size, sf::Texture *texture, const signed texW, const signed texH, sf::Sprite *sprite, Widget *parent = nullptr);

        int   onMouseMove  (Vect &pos);
        int  onMousePress  (Vect &pos);
        int onMouseRelease (Vect &pos);

        int draw(RenderTarget *rt);

    ~CrossbarH() {
        delete buttonTexture;
    }
};