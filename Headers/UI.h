#include "Widgets.h"
#include "DSL.h"
#include "Config.h"
#include "PluginManager.h"
#include "Tool.h"
#include "EditBox.h"

Window* orginiseMainScreen(sf::RenderWindow *window, FilterManager*, ToolManager*, PluginManager*,  EventManager *);

int addMainScreenButtons(Window *window, Menu *menu, Canvas *canvas, PluginManager*, EventManager *);

Menu *addFilterMenu(Button *filter, Canvas *canvas);

Menu *addToolsMenu(Button *tools, Canvas *canvas);

Menu *addColorMenu(Button *color, Canvas *canvas);

Menu *addWindowMenu(Window *mainWindow, Button *window);

Menu *addPluginMenu(Button *plugins, Canvas *, PluginManager *pluginManager, EventManager *);

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
