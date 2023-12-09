#include "../Headers/Tool.h"
#include "../Headers/DSL.h"
#include "../Headers/RenderTarget.h"

void Brush::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    drawing = Drawing::Enable;

    this -> startPoint = this -> lastPoint = curPos;

    return;
}

void Brush::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    sf::RenderTexture * rt  = (dynamic_cast<RenderTarget *> (data)) -> getWindow();
    sf::RenderTexture *temp = (dynamic_cast<RenderTarget *> (tmp) ) -> getWindow();
    
    if (drawing == Drawing::Disable) return;

    float radius = 8;

    sf::CircleShape circle(radius);
    circle.setPosition(lastPoint.x - radius, lastPoint.y - radius);
    circle.setFillColor(translateColor(color));
    rt->draw(circle);
    circle.setPosition(curPos.x - radius, curPos.y - radius);
    rt->draw(circle);

    sf::ConvexShape polygon;

    Vect dir = curPos - lastPoint;
    Vect  n  = !(Vect(-dir.y, dir.x)) * radius;

    polygon.setPointCount(4);
    polygon.setPoint(0, sf::Vector2f(lastPoint.x - n.x, lastPoint.y - n.y));
    polygon.setPoint(1, sf::Vector2f(lastPoint.x + n.x, lastPoint.y + n.y));
    polygon.setPoint(2, sf::Vector2f(   curPos.x + n.x,    curPos.y + n.y));
    polygon.setPoint(3, sf::Vector2f(   curPos.x - n.x,    curPos.y - n.y));

    polygon.setFillColor(translateColor(color));

    rt -> draw(polygon);

    this -> lastPoint = curPos;
}

void Brush::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void Brush::disable(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void PolyLine::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    if (drawing == Enable) return;

    drawing = Drawing::Enable;

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) {
        this -> startPoint = this -> lastPoint = curPos;
    } else {
        data -> drawLine({lastPoint.x, lastPoint.y}, context.position, color);
        lastPoint = curPos;
    }

    return;
}

void PolyLine::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );
    
    if (lastPoint.x == - 1 || lastPoint.y == -1) return;

    Vect curPos = Vect(context.position.x, context.position.y);

    tmp -> drawLine({lastPoint.x, lastPoint.y}, context.position, color);
}

void PolyLine::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void PolyLine::disable(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    lastPoint = Vect(-1, -1);
    drawing = Drawing::Disable;

    return;
}

void Pen::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Enable;

    Vect curPos = Vect(context.position.x, context.position.y);

    this -> startPoint = this -> lastPoint = curPos;

    return;
}

void Pen::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    if (drawing == Drawing::Disable) return;

    data -> drawLine({lastPoint.x, lastPoint.y}, {curPos.x, curPos.y}, color);
    lastPoint = curPos;

    return;
}

void Pen::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void Pen::disable(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void Eraser::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Enable;
    Vect curPos = Vect(context.position.x, context.position.y);

    this -> startPoint = this -> lastPoint = curPos;

    return;
}

void Eraser::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    sf::RenderTexture * rt  = (dynamic_cast<RenderTarget *> (data)) -> getWindow();
    sf::RenderTexture *temp = (dynamic_cast<RenderTarget *> (tmp) ) -> getWindow();
    
    if (drawing == Drawing::Disable) return;

    this -> lastPoint = curPos;

    sf::CircleShape circle(8);
    circle.setPosition(curPos.x, curPos.y);
    circle.setFillColor(sf::Color::White);
    rt->draw(circle);
}

void Eraser::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;
    
    return;
}

void Eraser::disable(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;
    
    return;
}


void Square::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    if (drawing == Drawing::Enable) return;

    drawing = Drawing::Enable;

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) {
        this -> startPoint = this -> lastPoint = curPos;
    } else {
        data -> drawRect({startPoint.x, startPoint.y}, {curPos.x - startPoint.x, curPos.y - startPoint.y}, color);
        startPoint = Vect(-1, -1);
    }

    return;
}

void Square::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) return;

    tmp -> drawRect({startPoint.x, startPoint.y}, {curPos.x - startPoint.x, curPos.y - startPoint.y}, color);

    return;
}

void Square::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void Square::disable(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    startPoint = Vect(-1, -1);
    drawing = Drawing::Disable;

    return;
}

void Circle::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    if (drawing == Drawing::Enable) return;

    drawing = Drawing::Enable;

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) {
        this -> startPoint = this -> lastPoint = curPos;
    } else {
        float diam = ((abs(curPos.x - startPoint.x) < abs(curPos.y - startPoint.y))? abs(curPos.x - startPoint.x) : abs(curPos.y - startPoint.y));
        Vect circlePos;

        if (startPoint.x < curPos.x)
            circlePos.x = startPoint.x;
        if (startPoint.y < curPos.y)
            circlePos.y = startPoint.y;

        if (startPoint.x > curPos.x)
            circlePos.x = startPoint.x - diam;
        if (startPoint.y > curPos.y)
            circlePos.y = startPoint.y - diam;

        data -> drawEllipse({circlePos.x, circlePos.y}, {diam / 2, diam / 2}, color);

        startPoint = Vect(-1, -1);
    }

    return;
}

void Circle::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) return;

    float diam = ((abs(curPos.x - startPoint.x) < abs(curPos.y - startPoint.y))? abs(curPos.x - startPoint.x) : abs(curPos.y - startPoint.y));

    Vect circlePos;

    if (startPoint.x < curPos.x)
        circlePos.x = startPoint.x;
    if (startPoint.y < curPos.y)
        circlePos.y = startPoint.y;

    if (startPoint.x > curPos.x)
        circlePos.x = startPoint.x - diam;
    if (startPoint.y > curPos.y)
        circlePos.y = startPoint.y - diam;


    tmp -> drawEllipse({circlePos.x, circlePos.y}, {diam / 2, diam / 2}, color);

    return;
}

void Circle::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void Circle::disable(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    startPoint = Vect(-1, -1);
    drawing = Drawing::Disable;

    return;
}

void ToolManager::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    tool->paintOnPress(data, tmp, context, color);

    return;
}

void ToolManager::paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp , /*nothing*/ );

    tool->paintOnMove(data, tmp, context, color);

    return;
}

void ToolManager::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp , /*nothing*/ );

    tool->paintOnRelease(data, tmp, context, color);

    return;
}

void ToolManager::disableTool(RenderTargetI *data, RenderTargetI *tmp, MouseContext context) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp , /*nothing*/ );

    tool->disable(data, tmp, context, color);

    return;
}

void ToolManager::setTool(ToolI *tool) {
    catchNullptr(tool, );

    if (this -> tool != nullptr) delete this -> tool;
    this -> tool = tool;

    return;
}