#include "Widgets.h"

Window* orginiseMainScreen(sf::RenderWindow *window);

int addMainScreenButtons(Menu *menu, Canvas *canvas);

Menu *addToolsMenu(Button *tools, Canvas *canvas);

Menu *addColorMenu(Button *color, Canvas *canvas);

Menu *addWindowMenu(Button *window);

Window *addSubWindow(Vect pos);

int activateWidget(Button *button);

int setPen(Button *button);

int setRubber(Button *button);

int setBrush(Button *button);

int setRed(Button *button);

int setGreen(Button *button);

int setBlue(Button *button);
