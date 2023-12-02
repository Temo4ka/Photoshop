#include "../Headers/EditBox.h"


void ModalWindow::setParamNames(plugin::Array<const char *> paramNames) {
    this->paramNames = paramNames;

    setPosition(Vect(150, std::max(0ULL, (WINDOW_HEIGHT - EDIT_BOX_HEIGHT * paramNames.size) / 2) ));
    setSizeVect(Vect(720, EDIT_BOX_HEIGHT * paramNames.size + 200));

    sf::Image *image = new sf::Image;
    image -> loadFromFile(EDITBOX_FILE_NAME);

    sf::Texture *texture = new sf::Texture;
    texture -> loadFromImage(*image);

    for (int cur = 0; cur < paramNames.size; cur++) {
        EditBox *editBox = new EditBox(Vect((THIS_SIZE.x / 2 + 5) + POSITION.x,
                                             POSITION.y + 50 + EDIT_BOX_HEIGHT * cur), 
                                       Vect((THIS_SIZE.x / 2 - 10), EDIT_BOX_HEIGHT), texture,
                                       EDIT_BOX_WIDTH, EDIT_BOX_HEIGHT, new sf::Sprite);

        editBox -> changeStatus();

        addSubWidget(editBox);
    }

    sf::Font *font = new sf::Font;
    font -> loadFromFile("./Font/newFont.ttf");

    texture = new sf::Texture; 
    texture -> loadFromFile(BUTTON_FILE_NAME);

    Button *okButton = new Button(Vect(POSITION.x + 300, POSITION.y + THIS_SIZE.y - 30), Vect(50, 30), "ok", font, texture, new sf::Sprite,
                                  modalWindowButton);

    okButton->getText()->setPosition(POSITION.x + 308, POSITION.y + THIS_SIZE.y - 24);

    addSubWidget(okButton);

    okButton -> changeStatus();
    okButton -> addSubWidget(this);

    return;
}

plugin::Array<double> ModalWindow::getParams() {
    ListNode<Widget>* curNode = (this -> getList()) -> getHead();

    params = Array<double>(paramNames.size, (double *) calloc(paramNames.size, sizeof(double)));

    for (int cur = 0; cur < paramNames.size; cur++) {
        catchNullptr(curNode, Array<double> ());

        MSG("HERE")
        EditBox *curEditBox = dynamic_cast<EditBox*> (curNode -> getObject());
        params.data[cur] = curEditBox -> getNum();

        curNode = curNode -> getNext();
    }
    params.size = paramNames.size;

    return params;
}

int ModalWindow::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);
    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    ListNode<Region> *curRegionNode = ((this->getRegionSet())->getHead())->getHead();
    for (int i = 0; i < this->getRegionSet()->getSize(); i++) {
        Region *curRegion = curRegionNode->getObject();

        Vect curPos  = curRegion->getPos();
        Vect curSize = curRegion->getSize();
        Vect  scale  = this -> getScale();

        (this->getSprite())->setTextureRect(sf::IntRect(curPos.x - POSITION.x, curPos.y - POSITION.y,
                                                        curSize.x / scale.x, curSize.y / scale.y));

        (this->getSprite())->setPosition(curPos.x, curPos.y);

        (rt->getWindow())->draw(*(this->getSprite()));


        curRegionNode = curRegionNode -> getNext();
    }

    sf::Font font;
    font.loadFromFile(ARIAL_FONT_FILE_NAME);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);

    for (int cur = 0; cur < paramNames.size; cur++) {
        text.setString(paramNames.data[cur]);
        text.setPosition(POSITION.x + 5, POSITION.y + 10 + EDIT_BOX_HEIGHT * cur);

        (rt -> getWindow()) -> draw(text);
    }

    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);

        (cur -> getObject()) -> draw(rt);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}


int EditBox::onMousePress(Vect &pos) {
    isWriting = true;

    return EXIT_SUCCESS;
}

int EditBox::onMouseMove(Vect &pos) {
    if (!isInWidgetRegion(pos))
        isWriting = false;

    return EXIT_SUCCESS;
}

int EditBox::onMouseRelease(Vect &pos) {
    return EXIT_SUCCESS;
}

int EditBox::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);

    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    ListNode<Region> *curRegionNode = ((this->getRegionSet())->getHead())->getHead();
    for (int i = 0; i < this->getRegionSet()->getSize(); i++) {
        Region *curRegion = curRegionNode->getObject();

        Vect curPos  = curRegion->getPos();
        Vect curSize = curRegion->getSize();
        Vect  scale  = this -> getScale();

        (this->getSprite())->setTextureRect(sf::IntRect(curPos.x - POSITION.x, curPos.y - POSITION.y,
                                                        curSize.x / scale.x, curSize.y / scale.y));

        (this->getSprite())->setPosition(curPos.x, curPos.y);

        (rt->getWindow())->draw(*(this->getSprite()));

        curRegionNode = curRegionNode -> getNext();
    }

    sf::Text text;
    text.setFont(*font);
    text.setString(curString);
    text.setPosition(POSITION.x + 10 * getScale().x, POSITION.y + 10);
    text.setFillColor(sf::Color::Black);

    (rt->getWindow()) -> draw(text);

    sf::FloatRect curRect = text.getGlobalBounds();

    Vect cursorPosition = Vect(curRect.left + curRect.width, curRect.top - 4);

    sf::RectangleShape cursor;
    cursor.setPosition(cursorPosition.x, cursorPosition.y);
    cursor.setSize(sf::Vector2f(3, 35));
    cursor.setFillColor(sf::Color::Black);

    (rt->getWindow()) -> draw(cursor);

    return EXIT_SUCCESS;
}


bool EditBox::onKeyboardPress(plugin::KeyboardContext context) {
    if (!isWriting) return EXIT_SUCCESS; 

    if (type == BoxType::Text) {
        if (context.key >= plugin::Key::A && context.key <= plugin::Key::Z) addNewLetter(translateLetter(context));

        if (context.key == plugin::Key::Space) addNewLetter(" ");
    }

    if (context.key >= plugin::Key::Num0 && context.key <= plugin::Key::Num9) {
        char *symb = new char;
        addNewLetter(itoa(int(context.key) - int(plugin::Key::Num0), symb, 10));
        delete symb;
    }

    if (context.key == plugin::Key::Period && !(isPeriodPlaced && type == BoxType::Num)) {
        addNewLetter(".");
        isPeriodPlaced = true;
    }

    if (context.key == plugin::Key::Backspace) eraseLetter();

    // MSG("UNKNOWN KEY!");
    return false;
}

bool EditBox::onKeyboardRelease (plugin::KeyboardContext context) {

    // MSG("UNKNOWN KEY!");
    return false;
}

void EditBox::eraseLetter() {
    if (curString.size()) {
        if (curString.back() == '.') isPeriodPlaced = false;
        curString.pop_back();
    }

    return;
}


void EditBox::addNewLetter(const char *letter) {
    catchNullptr(letter, );

    if (curString.size() < THIS_SIZE.x / 36)
        curString.push_back(*letter);

    return;
}

#define CASE(LETTER, letter)                     \
    case plugin::Key::LETTER:                     \
        return (context.shift? #LETTER : #letter); \
        break;

const char* EditBox::translateLetter(plugin::KeyboardContext context) {
    switch (context.key) {
        CASE(A, a);
        CASE(B, b);
        CASE(C, c);
        CASE(D, d);
        CASE(E, e);
        CASE(F, f);
        CASE(G, g);
        CASE(H, h);
        CASE(I, i);
        CASE(J, j);
        CASE(K, k);
        CASE(L, l);
        CASE(M, m);
        CASE(N, n);
        CASE(O, o);
        CASE(P, p);
        CASE(Q, q);
        CASE(R, r);
        CASE(S, s);
        CASE(T, t);
        CASE(U, u);
        CASE(V, v);
        CASE(W, w);
        CASE(X, x);
        CASE(Y, y);
        CASE(Z, z);

        default:
            return nullptr;
    }
    
}

#undef CASE

int modalWindowButton(Button *button) {
    catchNullptr(button, EXIT_FAILURE);

    ListHead<Widget> *list = button -> getList();

    Widget *curWidget = (list->getHead())->getObject();
    catchNullptr(curWidget, EXIT_FAILURE);

    curWidget->changeStatus();

    ModalWindow *modWind = dynamic_cast<ModalWindow*>(curWidget);

    catchNullptr(modWind->getInterface(), EXIT_FAILURE);
    modWind->getInterface()->setParams(modWind->getParams());

    modWind -> getEventManager()->setPriority(plugin::EventType::KeyPress, LOW_PRIORITY);

    return EXIT_SUCCESS; 
}

bool ModalWindow::onKeyboardPress(plugin::KeyboardContext context) {
    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return false;

    do {
        catchNullptr(cur -> getObject(), true);
        (cur -> getObject()) -> onKeyboardPress(context);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return false;
}

bool ModalWindow::onKeyboardRelease(plugin::KeyboardContext context) {
    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return false;

    do {
        catchNullptr(cur -> getObject(), true);
        (cur -> getObject()) -> onKeyboardRelease(context);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return false;
}