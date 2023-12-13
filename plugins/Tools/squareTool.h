#include "../../Headers/plugin.h"
#include "../../Headers/DSL.h"

using namespace plugin;

struct SquareTool : public ToolI {
    Vec2 startPoint;
    Vec2 lastPoint;

    enum Drawing {
        Disable = 0,
         Enable = 1
    } drawing;


    public:

        SquareTool():
        startPoint(Vec2(-1, -1)),
        lastPoint (Vec2(-1, -1)),
         drawing  (Drawing::Disable)
        {}

        Array<const char *> getParamNames() { return Array<const char*>();}        
        Array<double> getParams() { return Array<double>(); }
        void setParams(Array<double> params) { return; }
        
        const Texture *getIcon() {return nullptr; }

        void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
        void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
        void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
        void     disable    (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
        
        ~SquareTool() {}
};

class SquareToolPlugin : public Plugin {
    SquareTool *tool;

    public:

         SquareToolPlugin() {
            id = 0x2EDA2;
            name = "Square";
            type = InterfaceType::Tool;
            tool = new SquareTool;
        }

        void selectPlugin() {}

        Interface *getInterface() { return tool; }

        ~SquareToolPlugin() { delete tool; }
};

DllExport plugin::Plugin* getInstance(plugin::App *app) {
    return new SquareToolPlugin();
}