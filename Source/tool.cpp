#include "../Headers/Tool.h"
#include "../Headers/DSL.h"

sf::Color translateColor(Color color);

void Brush::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    drawing = Drawing::Enable;

    this -> startPoint = this -> lastPoint = curPos;

    return;
}

void Brush::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    sf::RenderTexture * rt  = ((RenderTarget *) data) -> getWindow();
    sf::RenderTexture *temp = ((RenderTarget *) tmp ) -> getWindow();
    
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
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void Polyline::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    sf::RenderTexture * rt  = ((RenderTarget *) data) -> getWindow();
    sf::RenderTexture *temp = ((RenderTarget *) tmp ) -> getWindow();

    if (drawing == Enable) return;

    drawing = Drawing::Enable;

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) {
        this -> startPoint = this -> lastPoint = curPos;
    } else {
        sf::Vertex vertices[] = {
            sf::Vertex(sf::Vector2f(lastPoint.x, lastPoint.y), translateColor(color)),
            sf::Vertex(sf::Vector2f(curPos.x, curPos.y), translateColor(color))
        };
        rt -> draw(vertices, 2, sf::Lines);
        lastPoint = curPos;
    }

    return;
}

void Polyline::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );
    
    Vect curPos = Vect(context.position.x, context.position.y);
    sf::RenderTexture * rt  = ((RenderTarget *) data) -> getWindow();
    sf::RenderTexture *temp = ((RenderTarget *) tmp ) -> getWindow();

    sf::Vertex vertices[] = {
        sf::Vertex(sf::Vector2f(lastPoint.x, lastPoint.y), translateColor(color)),
        sf::Vertex(sf::Vector2f(curPos.x, curPos.y), translateColor(color))
    };
    tmp -> draw(vertices, 2, sf::Lines);
}

void Polyline::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void Pen::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Enable;

    Vect curPos = Vect(context.position.x, context.position.y);

    this -> startPoint = this -> lastPoint = curPos;

    return;
}

void Pen::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    sf::RenderTexture * rt  = ((RenderTarget *) data) -> getWindow();
    sf::RenderTexture *temp = ((RenderTarget *) tmp ) -> getWindow();

    if (drawing == Drawing::Disable) return;

    sf::Vertex vertices[] = {
        sf::Vertex(sf::Vector2f(lastPoint.x, lastPoint.y), translateColor(color)),
        sf::Vertex(sf::Vector2f(curPos.x, curPos.y), translateColor(color))
    };
    rt -> draw(vertices, 2, sf::Lines);
    lastPoint = curPos;

    return;
}

void Pen::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}



void Eraser::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Enable;
    Vect curPos = Vect(context.position.x, context.position.y);

    this -> startPoint = this -> lastPoint = curPos;

    return;
}

void Eraser::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    sf::RenderTexture * rt  = ((RenderTarget *) data) -> getWindow();
    sf::RenderTexture *temp = ((RenderTarget *) tmp ) -> getWindow();
    
    if (drawing == Drawing::Disable) return;

    this -> lastPoint = curPos;

    sf::CircleShape circle(8);
    circle.setPosition(curPos.x, curPos.y);
    circle.setFillColor(sf::Color::White);
    rt->draw(circle);
}

void Eraser::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    return;
}

void Square::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    sf::RenderTexture * rt  = ((RenderTarget *) data) -> getWindow();
    sf::RenderTexture *temp = ((RenderTarget *) tmp ) -> getWindow();

    if (drawing == Drawing::Enable) return;

    drawing = Drawing::Enable;

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) {
        this -> startPoint = this -> lastPoint = curPos;
    } else {
        sf::RectangleShape rectangle(sf::Vector2f(curPos.x - startPoint.x, curPos.y - startPoint.y));
        rectangle.setPosition(startPoint.x, startPoint.y);
        rectangle.setFillColor(translateColor(color));
        rt -> draw(rectangle);
        startPoint = Vect(-1, -1);
    }

    return;
}

void Square::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    sf::RenderTexture * rt  = ((RenderTarget *) data) -> getWindow();
    sf::RenderTexture *temp = ((RenderTarget *) tmp ) -> getWindow();


    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) return;

    sf::RectangleShape rectangle(sf::Vector2f(curPos.x - startPoint.x, curPos.y - startPoint.y));
    rectangle.setPosition(startPoint.x, startPoint.y);
    rectangle.setFillColor(translateColor(color));
    tmp -> draw(rectangle);

    return;
}

void Square::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void Circle::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    sf::RenderTexture * rt  = ((RenderTarget *) data) -> getWindow();
    sf::RenderTexture *temp = ((RenderTarget *) tmp ) -> getWindow();

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
        circle.setFillColor(translateColor(color));
        rt -> draw(circle);

        startPoint = Vect(-1, -1);
    }

    return;
}

void Circle::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vect curPos = Vect(context.position.x, context.position.y);

    sf::RenderTexture * rt  = ((RenderTarget *) data) -> getWindow();
    sf::RenderTexture *temp = ((RenderTarget *) tmp ) -> getWindow();

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
    circle.setFillColor(translateColor(color));
    tmp -> draw(circle);

    return;
}

void Circle::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void ToolManager::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    tool->paintOnPress(data, tmp, curPos, color);

    return;
}

void ToolManager::paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    tool->paintOnMove(data, tmp, context, color);

    return;
}


void ToolManager::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context) {
    catchNullptr(rt , /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    tool->paintOnRelease(data, tmp, context, color);

    return;
}

sf::Color translateColor(Color color) {
    return sf::Color(translateColor(color).r, translateColor(color).g, translateColor(color).b, translateColor(color).a);
}