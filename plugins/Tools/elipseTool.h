#include "../../Headers/plugin.h"
#include "../../Headers/DSL.h"

using namespace plugin;

struct ElipseTool : public ToolI {
    Vec2 startPoint;
    Vec2 lastPoint;

    enum Drawing {
        Disable = 0,
         Enable = 1
    } drawing;


    public:

        ElipseTool():
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
        
        ~ElipseTool() {}
};

class ElipseToolPlugin : public Plugin {
    ElipseTool *tool;

    public:

         ElipseToolPlugin() {
            id = 0x1EDA1;
            name = "Elipse";
            type = InterfaceType::Tool;
            tool = new ElipseTool;
        }

        Interface *getInterface() { return tool; }

        ~ElipseToolPlugin() { delete tool; }

};