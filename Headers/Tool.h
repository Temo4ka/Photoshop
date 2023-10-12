#pragma once
#include "Vect.h"
#include <SFML/Graphics.hpp>

struct T;

struct TMan {
    T* t;
    sf::Color c;

    TMan():
    t(nullptr),
    c(sf::Color::Blue)
    {}

    void p(sf::RenderTexture *rt, sf::RenderTexture *t, Vect cp);
    void m(sf::RenderTexture *rt, sf::RenderTexture *t, Vect cp);
    void r(sf::RenderTexture *rt, sf::RenderTexture *t, Vect cp);
};

struct T {
    Vect sp;
    Vect lp;

    T():
    sp(Vect(-1, -1)),
    lp(Vect(-1, -1))
    {}

    virtual void p(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl) = 0;
    virtual void m(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl) = 0;
    virtual void r(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl) = 0;
};

// struct Sl : public T {

//     void p(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl);
//     void m(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl);
//     void r(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl);
// }


struct Pl : public T {

    void p(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl);
    void m(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl);
    void r(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl);
};

struct B : public T {

    void p(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl);
    void m(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl);
    void r(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl);
};

// struct F : public T {

//     void p(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl);
//     void m(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl);
//     void r(sf::RenderTexture *rt, sf::RenderTexture *t, Vect c, sf::Color cl);
// }