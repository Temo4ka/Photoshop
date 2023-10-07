#include "../Headers/UI.h"
#include "../Headers/DSL.h"
#include "../Headers/Config.h"

Window* orginiseMainScreen(sf::RenderWindow *window) {
    catchNullptr(  window  , nullptr);

    sf::Texture *texture = new sf::Texture;
    texture -> loadFromFile("./Image/test.jpeg");
    
    sf::Sprite *sprite = new sf::Sprite;

    Window *mainWindow = new Window(Vect(0 , 0), Vect(WINDOW_WIDTH, WINDOW_HEIGHT), texture, sprite);

    Menu *menu = new Menu(Vect(0, PANEL_HEIGHT), Vect(WINDOW_WIDTH, MENU_HEIGHT));

    if (addMainScreenButtons(menu)) return nullptr;

    menu -> turnOn();

    ListHead<Widget> *list = mainWindow -> getList();
    list -> pushBack(menu);

    mainWindow -> turnOn();

    return mainWindow;
}

int addMainScreenButtons(Menu *menu) {
    catchNullptr(menu, EXIT_FAILURE);

    Vect menuButtonSize(BUTTON_MENU_WIDTH, MENU_HEIGHT);

    sf::Font *font = new sf::Font;
    font -> loadFromFile("./Font/newFont.ttf");

    sf::Texture *texture = new sf::Texture; 
    texture -> loadFromFile("./Image/button1.jpg");

    sf::Sprite * fileS  = new sf::Sprite;
    sf::Sprite * editS  = new sf::Sprite;
    sf::Sprite * viewS  = new sf::Sprite;
    sf::Sprite *colorsS = new sf::Sprite;
    sf::Sprite *toolsS  = new sf::Sprite;
    sf::Sprite *windowS = new sf::Sprite;

    Button * file  = new Button(Vect(BUTTON_MENU_WIDTH * 0, PANEL_HEIGHT), menuButtonSize, " file ", font, texture,  fileS );
    Button * edit  = new Button(Vect(BUTTON_MENU_WIDTH * 1, PANEL_HEIGHT), menuButtonSize, " edit ", font, texture,  editS );
    Button * view  = new Button(Vect(BUTTON_MENU_WIDTH * 2, PANEL_HEIGHT), menuButtonSize, " view ", font, texture,  viewS );
    Button *colors = new Button(Vect(BUTTON_MENU_WIDTH * 5, PANEL_HEIGHT), menuButtonSize, "colors", font, texture, colorsS);
    Button *tools  = new Button(Vect(BUTTON_MENU_WIDTH * 4, PANEL_HEIGHT), menuButtonSize, "tools ", font, texture, toolsS );
    Button *window = new Button(Vect(BUTTON_MENU_WIDTH * 3, PANEL_HEIGHT), menuButtonSize, "window", font, texture, windowS);

    ListHead<Widget> *list = menu -> getList();

     file  -> turnOn();
     edit  -> turnOn();
     view  -> turnOn();
    colors -> turnOn();
    tools  -> turnOn();
    window -> turnOn();

    list -> pushBack( file );
    list -> pushBack( edit );
    list -> pushBack( view );
    list -> pushBack(colors);
    list -> pushBack(tools );
    list -> pushBack(window);

    return EXIT_SUCCESS;
}
 