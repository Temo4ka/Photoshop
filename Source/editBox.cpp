#include "../Headers/EditBox.h"


void ModalWindow::setParamNames(plugin::Array<const char *> paramNames) {
    this->paramsNames = paramNames;

    setPosition(Vect(150, std::max(0, (WINDOW_HEIGHT - EDIT_BOX_HEIGHT * paramNames.size) / 2) ));
    setSize(Vect(720, EDIT_BOX_HEIGHT * paramNames.size + 20));

    sf::Image *image = new Image;
    image -> loadFromFile(EDITBOX_FILE_NAME);

    sf::Texture *texture = new sf::Texture;
    texture -> loadFromImage(image);

    for (int cur = 0; cur < paramNames.size; cur++) {
        EditBox *editBox = new EditBox(Vect((WINDOW_WIDTH / 2 + 5) * getScale().x + POSITION.x,
                                             POSITION.y + 10 + EDIT_BOX_HEIGHT * cur), 
                                       Vect((THIS_SIZE.x / 2 - 10), EDIT_BOX_HEIGHT), texture,
                                       EDIT_BOX_WIDTH, EDIT_BOX_HEIGHT, new sf::Sprite);

        addSubWidget(editBox);
    }

    return;
}

plugin::Array<double> ModalWindow::getParams() {
    ListNode<Widget>* cur = (this -> getList()) -> getHead();

    for (int cur = 0; cur < paramNames.size; cur++) {
        catchNullptr(cur);

        EditBox *curEditBox = dynamic_cast<EditBox*> (cur -> getObject());
        params.data[cur] = curEditBox -> getNum();
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
    text.setColor(sf::Color::Black);

    for (int cur = 0; cur < paramNames.size; cur++) {
        text.setString(paramNames.data[cur]);
        text.setPosition(POSITION.x + 5, POSITION.y + 10 + EDIT_BOX_HEIGHT * cur);

        draw(text);
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

    return Window::onMousePress(pos);
}

int EditBox::onMouseMove(Vect &pos) {
    if (!isInWidgetRegion(pos))
        isWriting = false;

    return Window::onMouseMove(pos);
}

int EditBox::onMouseRelease(Vect &pos) {
    return Window::onMouseRelease(pos);
}

int EditBox::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);

    Window::draw(rt);

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


int EditBox::onKeyPressed (plugin::KeyboardContext context) {
    if (!isWriting) return EXIT_SUCCESS; 

    if (type == BoxType::Text) {
        if (context.key >= KeyBoard::A && context.key <= KeyBoard::Z) addNewLetter(translateLetter(context));

        if (context.key == KeyBoard::Space) addNewLetter(" ");
    }

    if (context.key >= KeyBoard::Num0 && context.key <= KeyBoard::Num9) {
        char *symb = new char;
        addNewLetter(itoa(context.key - KeyBoard::Num0, symb, 10));
        delete symb;
    }

    if (context.key == KeyBoard::Period && !(isPeriodPlaced && type == BoxType::Num)) {
        addNewLetter(".");
        isPeriodPlaced = true;
    }

    if (context.key == KeyBoard::Backspace) eraseLetter();

    // MSG("UNKNOWN KEY!");
    return EXIT_SUCCESS;
}

int EditBox::onKeyReleased (plugin::KeyboardContext context) {
    if (context.key == KeyBoard::LShift) capsLocked = false;

    // MSG("UNKNOWN KEY!");
    return EXIT_SUCCESS;
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

    MESSAGE("%lg", THIS_SIZE.x / 36);
    if (curString.size() < THIS_SIZE.x / 36)
        curString.push_back(*letter);

    return;
}

#define CASE(LETTER, letter)                     \
    case plugin::Key::LETTER:                     \
        return (context.shift? #LETTER : #letter); \
        break;

const char* EditBox::translateLetter(plugin::KeyboardContext context) {
    switch (letter) {
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
