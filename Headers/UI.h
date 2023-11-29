#include "../Headers/DSL.h"
#include "../Headers/Config.h"
#include "../Headers/PluginManager.h"
#include "../Headers/Tool.h"
#include "Widgets.h"

Window* orginiseMainScreen(sf::RenderWindow *window, FilterManager*, ToolManager*, PluginManager*);

int addMainScreenButtons(Window *window, Menu *menu, Canvas *canvas, PluginManager*);

Menu *addFilterMenu(Button *filter, Canvas *canvas);

Menu *addToolsMenu(Button *tools, Canvas *canvas);

Menu *addColorMenu(Button *color, Canvas *canvas);

Menu *addWindowMenu(Window *mainWindow, Button *window);

Menu *addPluginMenu(Button *plugins, Canvas *, PluginManager *pluginManager);

int activatePluginButton(Button *button);

Window *addSubWindow(Vect pos);

int activateWidget(Button *button);

void clipRegions(Window *window);

/*Colors---------------------*/
int setGreen(Button *button);
int  setRed (Button *button);
int setBlue (Button *button);
/*---------------------------*/

/*Tools------------------------*/
int setPolyLine(Button *button);
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
