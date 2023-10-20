#include "Widgets.h"

Window* orginiseMainScreen(sf::RenderWindow *window);

int addMainScreenButtons(Window *window, Menu *menu, Canvas *canvas);

Menu *addToolsMenu(Button *tools, Canvas *canvas);

Menu *addColorMenu(Button *color, Canvas *canvas);

Menu *addWindowMenu(Button *window);

Window *addSubWindow(Vect pos);

int activateWidget(Button *button);

void clipRegions(Window *window);

int setRed(Button *button);

int setGreen(Button *button);

int setBlue(Button *button);
