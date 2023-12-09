#include "../Headers/UI.h"

Window* orginiseMainScreen(sf::RenderWindow *window, HostApp *app) {
    catchNullptr(  window  , nullptr);
    catchNullptr(   app    , nullptr);

    sf::Texture *texture = new sf::Texture;
    texture -> loadFromFile(WINDOW_FILE_NAME);
    
    sf::Sprite *sprite = new sf::Sprite;

    Window *mainWindow = new Window(Vect(0 , 0), Vect(WINDOW_WIDTH, WINDOW_HEIGHT), texture, sprite);

    ModalWindow *modalWindow = new ModalWindow(nullptr, texture);
    modalWindow -> setApp(app);

    Menu *menu = new Menu(Vect(0, PANEL_HEIGHT), Vect(WINDOW_WIDTH, MENU_HEIGHT));

    Canvas *canvas = new Canvas(Vect(6, PANEL_HEIGHT + MENU_HEIGHT), Vect(MAIN_CANVAS_WIDTH, MAIN_CANVAS_HEIGHT), app);

    app->  mainCanvas =   canvas  ;
    app->   mainMenu  =    menu   ;
    app->     root    = mainWindow;
    app-> modalWindow = modalWindow;

           menu->setRoot(mainWindow);
         canvas->setRoot(mainWindow);
    modalWindow->setRoot(mainWindow);

    if (addMainScreenButtons(app)) return nullptr;
    mainWindow->pushBackSubWidget(menu);
    mainWindow->pushBackSubWidget(canvas);
    mainWindow->pushBackSubWidget(modalWindow); 

     menu  -> changeStatus();
    canvas -> changeStatus();

    // ListHead<Widget> *list = mainWindow -> getList();
    // list -> pushBack(canvas);
    // list -> pushBack( menu );

    mainWindow -> changeStatus();

    return mainWindow;
}

int addMainScreenButtons(HostApp *app) {
    catchNullptr(app, EXIT_FAILURE);

    Vect menuButtonSize(BUTTON_MENU_WIDTH, MENU_HEIGHT);

    sf::Font *font = new sf::Font;
    font -> loadFromFile(FONT_FILE_NAME);

    sf::Texture *texture = new sf::Texture; 
    texture -> loadFromFile(BUTTON_FILE_NAME);

    const char *buttNames[] = {" file  ", "plugins", "filter ", "window ", "tools  ", "colors "};

    for (int curButt = 0; curButt < 6; curButt++) {
        Button *curButton = new Button(Vect(BUTTON_MENU_WIDTH * curButt, PANEL_HEIGHT), menuButtonSize, buttNames[curButt], font, texture, new sf::Sprite, 
                                        activateWidget);

        curButton -> changeStatus();

        app->mainMenu -> pushBackSubWidget(curButton);

        curButton -> setRoot(app->root);

        Menu *subMenu;
        switch (curButt) {
            case 0:
                subMenu = addFileMenu  (curButton, app);
                break;

            case 1: 
                subMenu = addPluginMenu(curButton, app);
                break;

            case 2:
                subMenu = addFilterMenu(curButton, app);
                break;

            case 3:
                subMenu = addWindowMenu(curButton, app);
                break;
            
            case 4:
                subMenu = addToolsMenu(curButton, app);
                break;
            
            case 5:
                subMenu   = addColorMenu(curButton, app);
                break;
            default: break;
        }

        app->root  -> pushBackSubWidget(subMenu);
        curButton  -> pushBackSubWidget(subMenu);
    }

    return EXIT_SUCCESS;
}

Menu *addFileMenu(Button *file, HostApp *app) {
    catchNullptr(file, nullptr);
    catchNullptr( app, nullptr);

    Vect pos  = file -> getPosition();
    Vect size = file -> getSizeVect();

    Vect menuButtonSize(BUTTON_MENU_WIDTH, MENU_HEIGHT);

    sf::Font *font = new sf::Font;
    font -> loadFromFile("./Font/newFont.ttf");

    sf::Texture *texture = new sf::Texture; 
    texture -> loadFromFile(BUTTON_FILE_NAME);

    Menu *fileMenu = new Menu(Vect(pos.x, pos.y + size.y), Vect(size.x, MENU_HEIGHT * 2));

    PluginButton *openButton = new PluginButton(nullptr, Vect(pos.x, pos.y + size.y * 1), menuButtonSize, " open ", font, texture, new sf::Sprite, openFile);
    PluginButton *saveButton = new PluginButton(nullptr, Vect(pos.x, pos.y + size.y * 2), menuButtonSize, " save ", font, texture, new sf::Sprite, saveFile);

    openButton -> setEventManager(app->eventManager);
    saveButton -> setEventManager(app->eventManager);
    openButton -> setApp (app);
    saveButton -> setApp (app);
    openButton -> setRoot(app->root);
    saveButton -> setRoot(app->root);
    openButton -> changeStatus();
    saveButton -> changeStatus();

    fileMenu -> pushBackSubWidget(openButton);
    fileMenu -> pushBackSubWidget(saveButton);

    openButton -> pushBackSubWidget(app->modalWindow);
    saveButton -> pushBackSubWidget(app->modalWindow);

    return fileMenu;
}

Menu *addFilterMenu(Button *filter, HostApp *app) {
    catchNullptr(filter, nullptr);
    catchNullptr( app  , nullptr);

    Vect pos  = filter -> getPosition();
    Vect size = filter -> getSizeVect();

    Vect menuButtonSize(BUTTON_MENU_WIDTH, MENU_HEIGHT);

    sf::Font *font = new sf::Font;
    font -> loadFromFile("./Font/newFont.ttf");

    sf::Texture *texture = new sf::Texture; 
    texture -> loadFromFile(BUTTON_FILE_NAME);

    sf::Sprite *reverseS = new sf::Sprite;
    sf::Sprite *recentS  = new sf::Sprite;

    Menu *filterMenu  = new Menu(Vect(pos.x, pos.y + size.y), Vect(size.x, MENU_HEIGHT * 2));

    Button * reverse  = new Button(Vect(pos.x, pos.y + size.y * 1), menuButtonSize, "Reverse", font, texture, reverseS,  setReverse  );
    Button * recent   = new Button(Vect(pos.x, pos.y + size.y * 2), menuButtonSize, "Recent ", font, texture, recentS , setLastFilter);

    reverse -> setRoot(app -> root);
     recent -> setRoot(app -> root);

    reverse -> changeStatus();
    recent  -> changeStatus();

    filterMenu -> pushBackSubWidget(reverse);
    filterMenu -> pushBackSubWidget(recent );

     reverse   -> pushBackSubWidget(app->mainCanvas);
     recent    -> pushBackSubWidget(app->mainCanvas);

    return filterMenu;
}

Menu *addColorMenu(Button *color, HostApp *app) {
    catchNullptr(color , nullptr);
    catchNullptr(app , nullptr);

    Vect pos  = color -> getPosition();
    Vect size = color -> getSizeVect();

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

    red   -> setRoot(app -> root);
    green -> setRoot(app -> root);
    blue  -> setRoot(app -> root);

    ListHead<Widget> *list = colorMenu -> getList();

     red  -> changeStatus();
    green -> changeStatus();
    blue  -> changeStatus();

    list -> pushBack( red );
    list -> pushBack(green);
    list -> pushBack(blue );

    list =  red  -> getList();
    list -> pushBack(app->mainCanvas);

    list = green -> getList();
    list -> pushBack(app->mainCanvas);

    list = blue  -> getList();
    list -> pushBack(app->mainCanvas);

    return colorMenu;
}

Menu *addWindowMenu(Button *window, HostApp *app) {
    catchNullptr(window, nullptr);

    Vect pos  = window -> getPosition();
    Vect size = window ->    getSizeVect   ();

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

    window1 -> setRoot(app->root);
    window2 -> setRoot(app->root);

    window1 -> changeStatus();
    window2 -> changeStatus();

    windowMenu -> pushBackSubWidget(window1);
    windowMenu -> pushBackSubWidget(window2);

    Window *win1 = createSubWindow(Vect(200, 400));
    Window *win2 = createSubWindow(Vect(900, 400));

    window1 -> pushBackSubWidget(win1);
    window2 -> pushBackSubWidget(win2);

    app->root -> pushBackSubWidget(win1);
    app->root -> pushBackSubWidget(win2);

    return windowMenu;
}

Menu *addToolsMenu(Button *tools, HostApp *app) {
    catchNullptr(tools, nullptr);
    catchNullptr(app, nullptr);

    Vect pos  = tools -> getPosition();
    Vect size = tools -> getSizeVect();

    Vect menuButtonSize(BUTTON_MENU_WIDTH, MENU_HEIGHT);

    sf::Font *font = new sf::Font;
    font -> loadFromFile("./Font/newFont.ttf");

    sf::Texture *texture = new sf::Texture; 
    texture -> loadFromFile(BUTTON_FILE_NAME);

    Menu *toolsMenu = new Menu(Vect(pos.x, pos.y + size.y), Vect(size.x, MENU_HEIGHT * 6));

    const char *toolNames[] = {"  pen   ", " brush  ", " eraser ", " circle ", " square ", "polyline" };

    int (*runFunctions[])(Button *) = { setPen, setBrush, setEraser, setCircle, setSquare, setPolyLine };

    for (int curTl = 0; curTl < 6; curTl++) {
        Button *curTool = new Button(Vect(pos.x, pos.y + size.y * (curTl + 1)),
                                     menuButtonSize, toolNames[curTl], font, texture, new sf::Sprite, runFunctions[curTl]);

        curTool -> setRoot(app -> root);

        curTool -> changeStatus();

        toolsMenu -> pushBackSubWidget(curTool);

        curTool -> pushBackSubWidget(app->mainCanvas);
    }

    return toolsMenu;
}

Menu *addPluginMenu(Button *plugins, HostApp *app) {
    catchNullptr(   plugins   , nullptr);
    catchNullptr(     app     , nullptr);

    Vect pos  = plugins -> getPosition();
    Vect size = plugins -> getSizeVect();

    Vect menuButtonSize(BUTTON_MENU_WIDTH, MENU_HEIGHT);

    sf::Font *font = new sf::Font;
    font -> loadFromFile("./Font/newFont.ttf");

    sf::Texture *texture = new sf::Texture; 
    texture -> loadFromFile(BUTTON_FILE_NAME);

    Menu *pluginMenu = new Menu(Vect(pos.x, pos.y + size.y), Vect(size.x, MENU_HEIGHT * app->pluginManager->pluginNum));

    ListNode<plugin::Plugin> *curNode = app->pluginManager->plugins.getHead();
    for (int cur = 1; cur <= app->pluginManager->pluginNum; cur++) {
        catchNullptr(curNode, nullptr);

        plugin::Plugin *curPlugin = (plugin::Plugin *) curNode -> getObject();

        PluginButton *curPluginButton = new PluginButton(curPlugin, Vect(pos.x, pos.y + size.y * cur), menuButtonSize, curPlugin->name, font,
                                                                         texture, new sf::Sprite, activatePluginButton);

        curPluginButton -> setRoot(app->root);

        curPluginButton -> setEventManager(app->eventManager);
        curPluginButton -> setApp (app);

        curPluginButton -> pushBackSubWidget(app->mainCanvas);

        curPluginButton -> changeStatus();
        
        pluginMenu -> pushBackSubWidget(curPluginButton);

        curNode = curNode -> getNext();
    }

    return pluginMenu;
}

Window *createSubWindow(Vect pos, Vect size) {
    sf::Texture *texture = new sf::Texture;
    texture -> loadFromFile(WINDOW_FILE_NAME);
    
    sf::Sprite *sprite = new sf::Sprite;

    Window *subWindow = new Window(pos, size, texture, sprite);

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

int setPolyLine(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    curCanvas->setTool(new PolyLine);
    return EXIT_SUCCESS;
}

int setReverse(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    curCanvas->setFilter(new ReverseFilter);
    return EXIT_SUCCESS;
}

int setLastFilter(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    curCanvas->activateFilter();
    return EXIT_SUCCESS;
}

int openFile(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    PluginButton *plugButt = dynamic_cast<PluginButton *>(button);

    if (plugButt->getEventManager() != nullptr) {
        catchNullptr(plugButt->getApp(), EXIT_FAILURE);

        ModalWindow *modWind = plugButt -> getApp() -> modalWindow;
        catchNullptr(modWind, EXIT_FAILURE);

        Array<const char *> paramNames(1, (const char **) calloc(1, sizeof(const char *)));
        paramNames.data[0] = "file name";

        modWind->setParamNames(paramNames, openFileWindowButton, EditBox::BoxType::Text);

        plugButt->getEventManager()->setPriority(plugin::EventType::KeyPress, HIGH_PRIORITY);

        modWind -> changeStatus();
    }


    return EXIT_SUCCESS;
}

int saveFile(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    PluginButton *plugButt = dynamic_cast<PluginButton *>(button);

    if (plugButt->getEventManager() != nullptr) {
        catchNullptr(plugButt->getApp(), EXIT_FAILURE);

        ModalWindow *modWind = plugButt -> getApp() -> modalWindow;
        catchNullptr(modWind, EXIT_FAILURE);

        Array<const char *> paramNames(1, (const char **) calloc(1, sizeof(const char *)));
        paramNames.data[0] = "new file Name";

        modWind->setParamNames(paramNames, saveFileWindowButton, EditBox::BoxType::Text);

        plugButt->getEventManager()->setPriority(plugin::EventType::KeyPress, HIGH_PRIORITY);

        modWind -> changeStatus();
    }


    return EXIT_SUCCESS;
}

void createModalWindow(PluginButton *plugButt);

int activatePluginButton(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    PluginButton *plugButt = dynamic_cast<PluginButton *>(button);

    ListHead<Widget> *list = button -> getList();

    Canvas *curCanvas = (Canvas *) (list->getHead())->getObject();
    catchNullptr(curCanvas, EXIT_FAILURE);

    createModalWindow(plugButt);

    if (plugButt->getPlugin()->type == plugin::InterfaceType::Filter) 
        curCanvas->setFilter(dynamic_cast<plugin::FilterI *> (plugButt->getPlugin()->getInterface()));
    else
        curCanvas->setTool  (dynamic_cast<plugin::ToolI   *> (plugButt->getPlugin()->getInterface()));

    return EXIT_SUCCESS;
}

void createModalWindow(PluginButton *plugButt) {
    catchNullptr(plugButt, );

    plugin::Interface *curI = plugButt->getPlugin()->getInterface();
    if (plugButt->getEventManager() != nullptr && curI->getParamNames().size) {
        ModalWindow *modWind = plugButt -> getApp() -> modalWindow;
        catchNullptr(modWind, );

        modWind -> setInterface(curI);

        modWind->setParamNames(plugButt->getPlugin()->getInterface()->getParamNames(), modalWindowButton);

        plugButt->getEventManager()->setPriority(plugin::EventType::KeyPress, HIGH_PRIORITY);
        // MSG("Here!")  

        modWind -> changeStatus();
    }

    return;
}

int modalWindowButton(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Widget *curWidget = (list->getHead())->getObject();
    catchNullptr(curWidget, EXIT_FAILURE);

    curWidget->changeStatus();

    ModalWindow *modWind = dynamic_cast<ModalWindow*>(curWidget);

    catchNullptr(modWind->getInterface(), EXIT_FAILURE);
    modWind->getInterface()->setParams(modWind->getParams());

    (modWind->getApp()->eventManager)->setPriority(plugin::EventType::KeyPress, LOW_PRIORITY);

    return EXIT_SUCCESS; 
}

void createNewImageWindow(const char *imageName, HostApp *app);

int openFileWindowButton(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Widget *curWidget = (list->getHead())->getObject();
    catchNullptr(curWidget, EXIT_FAILURE);

    curWidget->changeStatus();

    ModalWindow *modWind = dynamic_cast<ModalWindow*>(curWidget);
    catchNullptr(modWind, EXIT_FAILURE);

    Array<const char*> fileName = modWind->getStringParams();
    if (fileName.size == 0) return EXIT_FAILURE;

    char buffer[100] = "./files/";

    createNewImageWindow(strcat(buffer, fileName.data[0]), modWind -> getApp());
    
    (modWind->getApp()->eventManager)->setPriority(plugin::EventType::KeyPress, LOW_PRIORITY);

    return EXIT_SUCCESS;
}

void saveImageFromCanvas(const char *imageName, HostApp * app);

int saveFileWindowButton(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Widget *curWidget = (list->getHead())->getObject();
    catchNullptr(curWidget, EXIT_FAILURE);

    curWidget->changeStatus();

    ModalWindow *modWind = dynamic_cast<ModalWindow*>(curWidget);
    catchNullptr(modWind, EXIT_FAILURE);

    Array<const char*> fileName = modWind->getStringParams();
    if (fileName.size == 0) return EXIT_FAILURE;

    char buffer[100] = "./files/";

    saveImageFromCanvas(strcat(buffer, fileName.data[0]), modWind -> getApp());
    
    (modWind->getApp()->eventManager)->setPriority(plugin::EventType::KeyPress, LOW_PRIORITY);

    return EXIT_SUCCESS;
}


void clipRegions(Window *window) {
    RegionSet *set = window -> getRegionSet();
    delete set;
    set = new RegionSet();
    set -> addRegion(new Region(window -> getPosition(), window -> getSizeVect()));
    window -> setRegionSet(set);
    window -> clipRegions();

    return;
}

void saveImageFromCanvas(const char *imageName, HostApp * app) {
    catchNullptr(imageName, );
    catchNullptr(   app   , );

    plugin::Texture *texture = app->mainCanvas->getImage();

    sf::Image image;
    image.create(texture -> width, texture -> height, (const uint8_t*) texture -> pixels);
    image.saveToFile(imageName);

    return;
}


void createNewImageWindow(const char *imageName, HostApp *app) {
    catchNullptr(imageName, );
    catchNullptr(   app   , );

    sf::Texture texture;
    texture.loadFromFile(imageName);

    Vect textureSize = Vect(texture.getSize().x, texture.getSize().y);

    Canvas *newWindowCanvas = new Canvas(Vect(85, 130), textureSize, app);
    newWindowCanvas->changeStatus();

    sf::Sprite sprite;
    sprite.setTexture(texture);
    newWindowCanvas -> paint(&sprite);

    Window *wind = createSubWindow(Vect(80, 100), textureSize + Vect(10, 35));
    wind -> pushBackSubWidget(newWindowCanvas);
    wind -> changeStatus();

    app->root->pushFrontSubWidget(wind);
}