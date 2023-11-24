#include "Widget.h"

using namespace plugin;

struct Gui : GuiI {
    RenderTarget *rt;
    Widget *root;

    ListHead<RenderTarget> pluginRenders;

    public:

    Gui(RenderTarget *rt, Widget *root) :
                  rt (rt),
                            root (root)
    {}

    Vec2 getSize();
    RenderTargetI *getRenderTarget(Vec2 size, Vec2 pos, Plugin *self);
    void createParamWindow(Array<const char *> param_names, Interface *self);
    WidgetI* getRoot() { return root; }

    ~Gui() {
        delete rt;
        delete root;
    }
};
