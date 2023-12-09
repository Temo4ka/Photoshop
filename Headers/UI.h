#pragma once

#include "Widgets.h"
#include "DSL.h"
#include "Config.h"
#include "PluginManager.h"
#include "Tool.h"
#include "EditBox.h"

struct HostApp {
    ModalWindow   *modalWindow  ;
    ToolManager   *toolManager  ;
    FilterManager *filterManager;
    EventManager  *eventManager ;
    PluginManager *pluginManager;
       Window     *    root     ;
       Canvas     * mainCanvas  ;
        Menu      *  mainMenu   ;
};

Window* orginiseMainScreen(sf::RenderWindow *window, HostApp *app);

int addMainScreenButtons(HostApp *app);

Menu *addFileMenu(Button *file, HostApp *app);

Menu *addFilterMenu(Button *filter, HostApp *app);

Menu *addToolsMenu(Button *tools, HostApp *app);

Menu *addColorMenu(Button *color, HostApp *app);

Menu *addWindowMenu(Button *window, HostApp *app);

Menu *addPluginMenu(Button *plugins, HostApp *app);

int activatePluginButton(Button *button);

Window *createSubWindow(Vect pos, Vect size = Vect(SUBWINDOW_WIDTH, SUBWINDOW_HEIGHT));

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

int openFile(Button *button);

int openFileWindowButton(Button *button);

int modalWindowButton(Button *button);

int saveFile(Button *button);

int saveFileWindowButton(Button *button);