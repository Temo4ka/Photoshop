#include "../Headers/Tool.h"
#include "../Headers/DSL.h"

void Brush::onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Enable;

    this -> startPoint = this -> lastPoint = curPos;

    return;
}

void Brush::onMouseMove(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    if (drawing == Drawing::Disable) return;

    this -> lastPoint = curPos;

    sf::CircleShape circle(8);
    circle.setPosition(curPos.x, curPos.y);
    circle.setFillColor(color);
    rt->draw(circle);
}

void Brush::onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void Polyline::onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    if (drawing == Enable) return;

    drawing = Drawing::Enable;

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
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    sf::Vertex vertices[] = {
        sf::Vertex(sf::Vector2f(lastPoint.x, lastPoint.y), color),
        sf::Vertex(sf::Vector2f(curPos.x, curPos.y), color)
    };
    tmp -> draw(vertices, 2, sf::Lines);
}

void Polyline::onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void Pen::onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Enable;

    this -> startPoint = this -> lastPoint = curPos;

    return;
}

void Pen::onMouseMove(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    if (drawing == Drawing::Disable) return;

    sf::Vertex vertices[] = {
        sf::Vertex(sf::Vector2f(lastPoint.x, lastPoint.y), color),
        sf::Vertex(sf::Vector2f(curPos.x, curPos.y), color)
    };
    rt -> draw(vertices, 2, sf::Lines);
    lastPoint = curPos;

    return;
}

void Pen::onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void ToolManager::onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    tool->onMousePressed(rt, tmp, curPos, color);

    return;
}


void Eraser::onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Enable;

    this -> startPoint = this -> lastPoint = curPos;

    return;
}

void Eraser::onMouseMove(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    if (drawing == Drawing::Disable) return;

    this -> lastPoint = curPos;

    sf::CircleShape circle(8);
    circle.setPosition(curPos.x, curPos.y);
    circle.setFillColor(sf::Color::White);
    rt->draw(circle);
}

void Eraser::onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    return;
}

void Square::onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    if (drawing == Drawing::Enable) return;

    drawing = Drawing::Enable;

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) {
        this -> startPoint = this -> lastPoint = curPos;
    } else {
        sf::RectangleShape rectangle(sf::Vector2f(curPos.x - startPoint.x, curPos.y - startPoint.y));
        rectangle.setPosition(startPoint.x, startPoint.y);
        rectangle.setFillColor(color);
        rt -> draw(rectangle);
        startPoint = Vect(-1, -1);
    }

    return;
}

void Square::onMouseMove(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) return;

    sf::RectangleShape rectangle(sf::Vector2f(curPos.x - startPoint.x, curPos.y - startPoint.y));
    rectangle.setPosition(startPoint.x, startPoint.y);
    rectangle.setFillColor(color);
    tmp -> draw(rectangle);

    return;
}

void Square::onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void Circle::onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    if (drawing == Drawing::Enable) return;

    drawing = Drawing::Enable;

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) {
        this -> startPoint = this -> lastPoint = curPos;
    } else {
        float radius = ((abs(curPos.x - startPoint.x) < abs(curPos.y - startPoint.y))? abs(curPos.x - startPoint.x) : abs(curPos.y - startPoint.y)) / 2;
        Vect circlePos;

        if (startPoint.x < curPos.x)
            circlePos.x = startPoint.x;
        if (startPoint.y < curPos.y)
            circlePos.y = startPoint.y;

        if (startPoint.x > curPos.x)
            circlePos.x = startPoint.x - radius * 2;
        if (startPoint.y > curPos.y)
            circlePos.y = startPoint.y - radius * 2;


        sf::CircleShape circle(radius);
        circle.setPosition(circlePos.x, circlePos.y);
        circle.setFillColor(color);
        rt -> draw(circle);

        startPoint = Vect(-1, -1);
    }

    return;
}

void Circle::onMouseMove(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) return;

    float radius = ((abs(curPos.x - startPoint.x) < abs(curPos.y - startPoint.y))? abs(curPos.x - startPoint.x) : abs(curPos.y - startPoint.y)) / 2;

    Vect circlePos;

    if (startPoint.x < curPos.x)
        circlePos.x = startPoint.x;
    if (startPoint.y < curPos.y)
        circlePos.y = startPoint.y;

    if (startPoint.x > curPos.x)
        circlePos.x = startPoint.x - radius * 2;
    if (startPoint.y > curPos.y)
        circlePos.y = startPoint.y - radius * 2;


    sf::CircleShape circle(radius);
    circle.setPosition(circlePos.x, circlePos.y);
    circle.setFillColor(color);
    tmp -> draw(circle);

    return;
}

void Circle::onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos, sf::Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void ToolManager::onMouseMove(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    tool->onMouseMove(rt, tmp, curPos, color);

    return;
}


void ToolManager::onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *tmp, Vect curPos) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    tool->onMouseReleased(rt, tmp, curPos, color);

    return;
}