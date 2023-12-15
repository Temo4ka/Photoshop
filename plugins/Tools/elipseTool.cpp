#include <cmath>
#include "elipseTool.h"

void ElipseTool::paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vec2 curPos = Vec2(context.position.x, context.position.y);

    if (drawing == Drawing::Enable) return;

    drawing = Drawing::Enable;

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) {
        this -> startPoint = this -> lastPoint = curPos;
    } else {
        data -> drawEllipse({startPoint.x, startPoint.y}, {(curPos.x - startPoint.x) / 2, (curPos.y - startPoint.y) / 2}, color);
        startPoint = Vec2(-1, -1);
    }

    return;
}

void ElipseTool::paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    Vec2 curPos = Vec2(context.position.x, context.position.y);

    if (this -> startPoint.x == -1 && this -> startPoint.y == -1) return;

    tmp -> clear();
    tmp -> drawEllipse({startPoint.x, startPoint.y}, {(curPos.x - startPoint.x) / 2, (curPos.y - startPoint.y) / 2}, color);

    return;
}

void ElipseTool::paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    drawing = Drawing::Disable;

    return;
}

void ElipseTool::disable(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) {
    catchNullptr(data, /*nothing*/ );
    catchNullptr(tmp, /*nothing*/ );

    startPoint = Vec2(-1, -1);
    drawing = Drawing::Disable;

    return;
}

DllExport plugin::Plugin* getInstance(plugin::App *app) {
    return new ElipseToolPlugin();
}