#include "../Headers/Tool.h"

void Brush::onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    this -> startPoint = this -> lastPoint = curPos;

    return;
}

void Brush::onMouseMove(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    this -> lastPoint = curPos;

    sf::CircleShape circle(8);
    circle.setPosition(curPos.x, curPos.y);
    circle.setFillColor(color);
    rt->draw(circle);
}

void Brush::onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    return;
}

void Polyline::onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) {
        this -> startPoint = this -> lastPoint = curPos;
    } else {
        sf::Vertex vertices[] = {
            sf::Vertex(sf::Vector2f(lastPoint.x, lastPoint.y), color),
            sf::Vertex(sf::Vector2f(curPos.x, curPos.y), color)
        };
        rt -> draw(vertices, 2, sf::Lines);
        lastPoint = curPos;
    }

    return;
}

void Polyline::onMouseMove(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    sf::Vertex vertices[] = {
        sf::Vertex(sf::Vector2f(lastPoint.x, lastPoint.y), color),
        sf::Vertex(sf::Vector2f(curPos.x, curPos.y), color)
    };
    tmp -> draw(vertices, 2, sf::Lines);
}

void Polyline::onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    return;
}

void Pen::onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    this -> startPoint = this -> lastPoint = curPos;

    return;
}

void Pen::onMouseMove(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    sf::Vertex vertices[] = {
        sf::Vertex(sf::Vector2f(lastPoint.x, lastPoint.y), color),
        sf::Vertex(sf::Vector2f(curPos.x, curPos.y), color)
    };
    rt -> draw(vertices, 2, sf::Lines);
    lastPoint = curPos;

    return;
}

void Pen::onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    return;
}

void ToolManager::onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos) {
    catchNullptr(rt, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    tool->onMousePressed(rt, tmp, curPos, color);

    return;
}

void ToolManager::onMouseMove(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos) {
    catchNullptr(rt, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    tool->onMouseMove(rt, tmp, curPos, color);

    return;
}

void ToolManager::onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos) {
    catchNullptr(rt, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    tool->onMouseReleased(rt, tmp, curPos, color);

    return;
}