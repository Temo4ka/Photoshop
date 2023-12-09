#include "squareTool.h"
#include <algorithm>

void SquareTool::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vec2 curPos = Vec2(context.position.x, context.position.y);

    if (drawing == Drawing::Enable) return;

    drawing = Drawing::Enable;

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) {
        this -> startPoint = this -> lastPoint = curPos;
    } else {
        float a = std::min(abs(curPos.x - startPoint.x), abs(curPos.y - startPoint.y));

        data -> drawRect({startPoint.x, startPoint.y}, {a * (curPos.x - startPoint.x) / abs(curPos.x - startPoint.x),
                                                        a * (curPos.y - startPoint.y) / abs(curPos.y - startPoint.y)}, color);
        startPoint = Vec2(-1, -1);
    }

    return;
}

void SquareTool::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vec2 curPos = Vec2(context.position.x, context.position.y);

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) return;

    float a = std::min(abs(curPos.x - startPoint.x), abs(curPos.y - startPoint.y));

    tmp -> drawRect({startPoint.x, startPoint.y}, {a * (curPos.x - startPoint.x) / abs(curPos.x - startPoint.x),
                                                   a * (curPos.y - startPoint.y) / abs(curPos.y - startPoint.y)}, color);

    return;
}

void SquareTool::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void SquareTool::disable(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    startPoint = Vec2(-1, -1);
    drawing = Drawing::Disable;

    return;
}