#include "Widgets.h"

Window* orginiseMainScreen(sf::RenderWindow *window, FilterManager*, ToolManager*);

int addMainScreenButtons(Window *window, Menu *menu, Canvas *canvas);

Menu *addFilterMenu(Button *filter, Canvas *canvas);

Menu *addToolsMenu(Button *tools, Canvas *canvas);

Menu *addColorMenu(Button *color, Canvas *canvas);

Menu *addWindowMenu(Window *mainWindow, Button *window);

Window *addSubWindow(Vect pos);

int activateWidget(Button *button);

void clipRegions(Window *window);

/*Colors---------------------*/
int setGreen(Button *button);
int  setRed (Button *button);
int setBlue (Button *button);
/*---------------------------*/

/*Tools------------------------*/
int setPolyline(Button *button);
int   setPen   (Button *button);
int  setCircle (Button *button);
int  setSquare (Button *button);
int  setBrush  (Button *button);
int  setEraser (Button *button);
/*-----------------------------*/

/*Filters-----------------------*/
int setReverse(Button *button);
int setLastFilter(Button *button);
/*------------------------------*/
