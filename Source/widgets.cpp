#include "../Headers/Widgets.h"

int addWidget(Window *parent, Widget *child) {
    catchNullptr(parent, EXIT_FAILURE);
    catchNullptr(child , EXIT_FAILURE);

    int err = parent->addChild(child);
    EXECUTE_ERROR(err);

    return EXIT_SUCCESS;
}

int removeWidget(Window *parent, Widget *child) {
    catchNullptr(parent, EXIT_FAILURE);     
    catchNullptr(child , EXIT_FAILURE);

    int err = parent->removeChild(child);
    EXECUTE_ERROR(err);

    return EXIT_SUCCESS;
}

