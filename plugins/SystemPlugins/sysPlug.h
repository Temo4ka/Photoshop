#include "../../Headers/plugin.h"
#include "../../Headers/Config.h"
#include "../../Headers/DSL.h"

using namespace plugin;

class ImageWidget: public PluginWidgetI {
    Texture texture;

    public:
        void render(RenderTargetI* texture);

        bool onMouseMove(MouseContext context);
        bool onMouseRelease(MouseContext context);
        bool onMousePress(MouseContext context);
        bool onKeyboardPress(KeyboardContext context) { return false; }
        bool onKeyboardRelease(KeyboardContext context) { return false; }

        bool onClock(uint64_t delta) { return false; }

	    virtual uint8_t getPriority() { return LOW_PRIORITY; }
};