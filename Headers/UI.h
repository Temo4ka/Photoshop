#include "Widgets.h"

Window* orginiseMainScreen(sf::RenderWindow *window);

int addMainScreenButtons(Window *window, Menu *menu, Canvas *canvas);

Menu *addToolsMenu(Button *tools, Canvas *canvas);

Menu *addColorMenu(Button *color, Canvas *canvas);

Menu *addWindowMenu(Window *mainWindow, Button *window);

Window *addSubWindow(Vect pos);

int activateWidget(Button *button);

void clipRegions(Window *window);

int setGreen(Button *button);
int  setRed (Button *button);
int setBlue (Button *button);

int setPolyline(Button *button);
int   setPen   (Button *button);
int  setCircle (Button *button);
int  setSquare (Button *button);
int  setBrush  (Button *button);
int  setEraser (Button *button);
