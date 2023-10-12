#include "../Headers/Tool.h"

void B::p(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect c, sf::Color cl) {
    this -> sp.x = this -> lp.x = c.x;
    this -> sp.y = this -> lp.y = c.y;

    return;
}

void B::m(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect c, sf::Color cl) {
    this -> lp.x = c.x;
    this -> lp.y = c.y;

    sf::CircleShape po(8);
    po.setPosition(c.x, c.y);
    po.setFillColor(cl);
    rt->draw(po);
}

void B::r(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect c, sf::Color cl) {
    return;
}

void Pl::p(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect c, sf::Color cl) {
    if (this -> sp.x == -1 && this -> sp.y == -1) {
        this -> sp.x = this -> lp.x = c.x;
        this -> sp.y = this -> lp.y = c.y;
    } else {
        sf::Vertex vertices[] = {
            sf::Vertex(sf::Vector2f(lp.x, lp.y), cl),
            sf::Vertex(sf::Vector2f(c.x, c.y), cl)
        };
        rt -> draw(vertices, 2, sf::Lines);
        lp.x = c.x;
        lp.y = c.y;
    }

    return;
}

void Pl::m(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect c, sf::Color cl) {
    sf::Vertex vertices[] = {
        sf::Vertex(sf::Vector2f(lp.x, lp.y), cl),
        sf::Vertex(sf::Vector2f(c.x, c.y), cl)
    };
    rt -> draw(vertices, 2, sf::Lines);
    lp.x = c.x;
    lp.y = c.y;
}

void Pl::r(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect c, sf::Color cl) {
    return;
}

void TMan::p(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect cp) {
    t->p(rt, tmp, cp, c);

    return;
}

void TMan::m(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect cp) {
    t->m(rt, tmp, cp, c);

    return;
}

void TMan::r(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect cp) {
    t->r(rt, tmp, cp, c);

    return;
}