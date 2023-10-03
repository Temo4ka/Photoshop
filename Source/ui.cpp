#include "../Headers/UI.h"
#include "../Headers/DSL.h"
#include "../Headers/Config.h"

int orginiseMainScreen(Window *mainWindow, sf::RenderWindow *window) {
    catchNullptr(mainWindow, EXIT_FAILURE);
    catchNullptr(  window  , EXIT_FAILURE);

    Menu *menu = new Menu(Vect(0, PANEL_HEIGHT), Vect(WINDOW_WIDTH, MENU_HEIGHT));
    if (addMainScreenButtons(menu)) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int addMainScreenButtons(Menu *menu) {
    catchNullptr(menu, EXIT_FAILURE);

    Vect menuButtonSize(BUTTON_MENU_WIDTH, MENU_HEIGHT);

    Font font;
    font.loadFromFile("./Font/newFont.ttf");

    Button * file  = new Button(Vect(BUTTON_MENU_WIDTH * 0, PANEL_HEIGHT), menuButtonSize, " file ", &font);
    Button * edit  = new Button(Vect(BUTTON_MENU_WIDTH * 1, PANEL_HEIGHT), menuButtonSize, " edit ", &font);
    Button * view  = new Button(Vect(BUTTON_MENU_WIDTH * 2, PANEL_HEIGHT), menuButtonSize, " view ", &font);
    Button *colors = new Button(Vect(BUTTON_MENU_WIDTH * 5, PANEL_HEIGHT), menuButtonSize, "colors", &font);
    Button *tools  = new Button(Vect(BUTTON_MENU_WIDTH * 4, PANEL_HEIGHT), menuButtonSize, "tools ", &font);
    Button *window = new Button(Vect(BUTTON_MENU_WIDTH * 3, PANEL_HEIGHT), menuButtonSize, "window", &font);

    return EXIT_SUCCESS;
}
