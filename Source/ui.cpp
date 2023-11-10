#include "../Headers/UI.h"
#include "../Headers/DSL.h"
#include "../Headers/Config.h"

Window* orginiseMainScreen(sf::RenderWindow *window) {
    catchNullptr(  window  , nullptr);

    sf::Texture *texture = new sf::Texture;
    texture -> loadFromFile(WINDOW_FILE_NAME);
    
    sf::Sprite *sprite = new sf::Sprite;

    Window *mainWindow = new Window(Vect(0 , 0), Vect(WINDOW_WIDTH, WINDOW_HEIGHT), texture, sprite);

    Menu *menu = new Menu(Vect(0, PANEL_HEIGHT), Vect(WINDOW_WIDTH, MENU_HEIGHT));

    Canvas *canvas = new Canvas(Vect(6, PANEL_HEIGHT + MENU_HEIGHT), Vect(MAIN_CANVAS_WIDTH, MAIN_CANVAS_HEIGHT));

    if (addMainScreenButtons(mainWindow, menu, canvas)) return nullptr;
    mainWindow ->addSubWidget(menu);
    mainWindow ->addSubWidget(canvas);

     menu  -> changeStatus();
    canvas -> changeStatus();

    // ListHead<Widget> *list = mainWindow -> getList();
    // list -> pushBack(canvas);
    // list -> pushBack( menu );

    mainWindow -> changeStatus();

    return mainWindow;
}

int addMainScreenButtons(Window *mainWindow, Menu *menu, Canvas *canvas) {
    catchNullptr(menu, EXIT_FAILURE);

    Vect menuButtonSize(BUTTON_MENU_WIDTH, MENU_HEIGHT);

    sf::Font *font = new sf::Font;
    font -> loadFromFile(FONT_FILE_NAME);

    sf::Texture *texture = new sf::Texture; 
    texture -> loadFromFile(BUTTON_FILE_NAME);

    sf::Sprite * fileS  = new sf::Sprite;
    sf::Sprite * editS  = new sf::Sprite;
    sf::Sprite * viewS  = new sf::Sprite;
    sf::Sprite *colorsS = new sf::Sprite;
    sf::Sprite *toolsS  = new sf::Sprite;
    sf::Sprite *windowS = new sf::Sprite;

    Button * file  = new Button(Vect(BUTTON_MENU_WIDTH * 0, PANEL_HEIGHT), menuButtonSize, " file ", font, texture,  fileS );
    Button * edit  = new Button(Vect(BUTTON_MENU_WIDTH * 1, PANEL_HEIGHT), menuButtonSize, " edit ", font, texture,  editS );
    Button * view  = new Button(Vect(BUTTON_MENU_WIDTH * 2, PANEL_HEIGHT), menuButtonSize, " view ", font, texture,  viewS );
    Button *window = new Button(Vect(BUTTON_MENU_WIDTH * 3, PANEL_HEIGHT), menuButtonSize, "window", font, texture, windowS, activateWidget);
    Button *tools  = new Button(Vect(BUTTON_MENU_WIDTH * 4, PANEL_HEIGHT), menuButtonSize, "tools ", font, texture, toolsS , activateWidget);
    Button *colors = new Button(Vect(BUTTON_MENU_WIDTH * 5, PANEL_HEIGHT), menuButtonSize, "colors", font, texture, colorsS, activateWidget);

     file  -> changeStatus();
     edit  -> changeStatus();
     view  -> changeStatus();
    colors -> changeStatus();
    tools  -> changeStatus();
    window -> changeStatus();

    menu -> addSubWidget( file );
    menu -> addSubWidget( edit );
    menu -> addSubWidget( view );
    menu -> addSubWidget(colors);
    menu -> addSubWidget(tools );
    menu -> addSubWidget(window);

    Menu *subMenu = addToolsMenu(tools, canvas);
    mainWindow -> addSubWidget(subMenu);
       tools   -> addSubWidget(subMenu); 

      subMenu   = addColorMenu(colors, canvas);
    mainWindow -> addSubWidget(subMenu);
      colors   -> addSubWidget(subMenu);

      subMenu   = addWindowMenu(mainWindow, window);
    mainWindow -> addSubWidget(subMenu);
      window   -> addSubWidget(subMenu);

    return EXIT_SUCCESS;
}
 
Menu *addToolsMenu(Button *tools, Canvas *canvas) {
    catchNullptr(tools, nullptr);
    catchNullptr(canvas, nullptr);

    Vect pos  = tools -> getPosition();
    Vect size = tools ->   getSize  ();

    Vect menuButtonSize(BUTTON_MENU_WIDTH, MENU_HEIGHT);

    sf::Font *font = new sf::Font;
    font -> loadFromFile("./Font/newFont.ttf");

    sf::Texture *texture = new sf::Texture; 
    texture -> loadFromFile(BUTTON_FILE_NAME);

    sf::Sprite *   penS    = new sf::Sprite;
    sf::Sprite *  brushS   = new sf::Sprite;
    sf::Sprite *  rubberS  = new sf::Sprite;
    sf::Sprite *  circleS  = new sf::Sprite;
    sf::Sprite *  squareS  = new sf::Sprite;
    sf::Sprite * polylineS = new sf::Sprite;

    Menu *toolsMenu = new Menu(Vect(pos.x, pos.y + size.y), Vect(size.x, MENU_HEIGHT * 6));

    Button *    pen   = new Button(Vect(pos.x, pos.y + size.y * 1), menuButtonSize, "  pen   ", font, texture,   penS   ,   setPen   );
    Button *  brush   = new Button(Vect(pos.x, pos.y + size.y * 2), menuButtonSize, " brush  ", font, texture,  brushS  ,  setBrush  );
    Button *  rubber  = new Button(Vect(pos.x, pos.y + size.y * 3), menuButtonSize, " eraser ", font, texture,  rubberS ,  setEraser );
    Button *  circle  = new Button(Vect(pos.x, pos.y + size.y * 4), menuButtonSize, " circle ", font, texture,  circleS ,  setCircle );
    Button *  square  = new Button(Vect(pos.x, pos.y + size.y * 5), menuButtonSize, " square ", font, texture,  squareS ,  setSquare );
    Button * polyline = new Button(Vect(pos.x, pos.y + size.y * 6), menuButtonSize, "polyline", font, texture, polylineS, setPolyline);

       pen   -> changeStatus();
     brush   -> changeStatus();
     rubber  -> changeStatus();
     circle  -> changeStatus();
     square  -> changeStatus();
    polyline -> changeStatus();

    toolsMenu -> addSubWidget(  pen   );
    toolsMenu -> addSubWidget( brush  );
    toolsMenu -> addSubWidget( rubber );
    toolsMenu -> addSubWidget( circle );
    toolsMenu -> addSubWidget( square );
    toolsMenu -> addSubWidget(polyline);

      pen    -> addSubWidget(canvas);
     brush   -> addSubWidget(canvas);
     rubber  -> addSubWidget(canvas);
     circle  -> addSubWidget(canvas);
     square  -> addSubWidget(canvas);
    polyline -> addSubWidget(canvas);

    return toolsMenu;
}

Menu *addColorMenu(Button *color, Canvas *canvas) {
    catchNullptr(color , nullptr);
    catchNullptr(canvas, nullptr);

    Vect pos  = color -> getPosition();
    Vect size = color ->   getSize  ();

    Vect menuButtonSize(BUTTON_MENU_WIDTH, MENU_HEIGHT);

    sf::Font *font = new sf::Font;
    font -> loadFromFile("./Font/newFont.ttf");

    sf::Texture *texture = new sf::Texture; 
    texture -> loadFromFile(BUTTON_FILE_NAME);

    sf::Sprite *  redS  = new sf::Sprite;
    sf::Sprite * greenS = new sf::Sprite;
    sf::Sprite * blueS  = new sf::Sprite;

    Menu *colorMenu = new Menu(Vect(pos.x, pos.y + size.y), Vect(size.x, MENU_HEIGHT * 3));

    Button *  red  = new Button(Vect(pos.x, pos.y + size.y * 1), menuButtonSize, " red ", font, texture,  redS ,  setRed );
    Button * green = new Button(Vect(pos.x, pos.y + size.y * 2), menuButtonSize, "green", font, texture, greenS, setGreen);
    Button * blue  = new Button(Vect(pos.x, pos.y + size.y * 3), menuButtonSize, "blue ", font, texture, blueS , setBlue );

    ListHead<Widget> *list = colorMenu -> getList();

     red  -> changeStatus();
    green -> changeStatus();
    blue  -> changeStatus();

    list -> pushBack( red );
    list -> pushBack(green);
    list -> pushBack(blue );

    list =  red  -> getList();
    list -> pushBack(canvas);

    list = green -> getList();
    list -> pushBack(canvas);

    list = blue  -> getList();
    list -> pushBack(canvas);

    return colorMenu;
}

Menu *addWindowMenu(Window *mainWindow, Button *window) {
    catchNullptr(window, nullptr);

    Vect pos  = window -> getPosition();
    Vect size = window ->   getSize  ();

    Vect menuButtonSize(BUTTON_MENU_WIDTH, MENU_HEIGHT);

    sf::Font *font = new sf::Font;
    font -> loadFromFile("./Font/newFont.ttf");

    sf::Texture *texture = new sf::Texture; 
    texture -> loadFromFile(BUTTON_FILE_NAME);

    sf::Sprite *window1S = new sf::Sprite;
    sf::Sprite *window2S = new sf::Sprite;

    Menu *windowMenu = new Menu(Vect(pos.x, pos.y + size.y), Vect(size.x, MENU_HEIGHT * 2));

    Button *window1 = new Button(Vect(pos.x, pos.y + size.y * 1), menuButtonSize, "window1", font, texture, window1S, activateWidget);
    Button *window2 = new Button(Vect(pos.x, pos.y + size.y * 2), menuButtonSize, "window2", font, texture, window2S, activateWidget);

    window1 -> changeStatus();
    window2 -> changeStatus();

    windowMenu -> addSubWidget(window1);
    windowMenu -> addSubWidget(window2);

    Window *win1 = addSubWindow(Vect(200, 400));
    Window *win2 = addSubWindow(Vect(900, 400));

    window1 -> addSubWidget(win1);
    window2 -> addSubWidget(win2);

    mainWindow -> addSubWidget(win1);
    mainWindow -> addSubWidget(win2);

    return windowMenu;
}

Window *addSubWindow(Vect pos) {
    sf::Texture *texture = new sf::Texture;
    texture -> loadFromFile(WINDOW_FILE_NAME);
    
    sf::Sprite *sprite = new sf::Sprite;

    Window *subWindow = new Window(pos, Vect(SUBWINDOW_WIDTH, SUBWINDOW_HEIGHT), texture, sprite);

    return subWindow;
}

int activateWidget(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    // FILE *logFile = fopen("logFile.txt", "a");
    // fprintf(logFile, "%s -> Here\n",  __PRETTY_FUNCTION__);
    // fclose(logFile);

    ListHead<Widget> *list = button -> getList();

    Widget *curWidget = (list->getHead())->getObject();
    catchNullptr(curWidget, EXIT_FAILURE);

    curWidget->changeStatus();
    return EXIT_SUCCESS; 
}

int setRed(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    // FILE *logFile = fopen("logFile.txt", "a");
    // fprintf(logFile, "%s -> Here\n",  __PRETTY_FUNCTION__);
    // fclose(logFile);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    curCanvas->setColor(sf::Color::Red);

    return EXIT_SUCCESS;
}

int setGreen(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    // FILE *logFile = fopen("logFile.txt", "a");
    // fprintf(logFile, "%s -> Here\n",  __PRETTY_FUNCTION__);
    // fclose(logFile);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    curCanvas->setColor(sf::Color::Green);

    return EXIT_SUCCESS;
}

int setBlue(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    // FILE *logFile = fopen("logFile.txt", "a");
    // fprintf(logFile, "%s -> Here\n",  __PRETTY_FUNCTION__);
    // fclose(logFile);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    curCanvas->setColor(sf::Color::Blue);

    return EXIT_SUCCESS;
}

int setPen(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    curCanvas->setTool(new Pen);
    return EXIT_SUCCESS;
}

int setBrush(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    curCanvas->setTool(new Brush);
    return EXIT_SUCCESS;
}

int setEraser(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    curCanvas->setTool(new Eraser);
    return EXIT_SUCCESS;
}

int setCircle(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    curCanvas->setTool(new Circle);
    return EXIT_SUCCESS;
}

int setSquare(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    curCanvas->setTool(new Square);
    return EXIT_SUCCESS;
}

int setPolyline(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    curCanvas->setTool(new Polyline);
    return EXIT_SUCCESS;
}

void clipRegions(Window *window) {
    RegionSet *set = window -> getRegionSet();
    delete set;
    set = new RegionSet();
    set -> addRegion(new Region(window -> getPosition(), window -> getSize()));
    window -> setRegionSet(set);
    window -> clipRegions();

    return;
}