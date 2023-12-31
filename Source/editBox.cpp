#include "../Headers/EditBox.h"


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


int EditBox::onKeyPressed (KeyBoard::Key key) {
    if (!isWriting) return EXIT_SUCCESS; 

    if (type == BoxType::Text) {
        if (key >= KeyBoard::A && key <= KeyBoard::Z) addNewLetter(translateLetter(key));

        if (key == KeyBoard::Space) addNewLetter(" ");

        if (key == KeyBoard::LShift) capsLocked = true;
    }

    if (key >= KeyBoard::Num0 && key <= KeyBoard::Num9) {
        char *symb = new char;
        addNewLetter(itoa(key - KeyBoard::Num0, symb, 10));
        delete symb;
    }

    if (key == KeyBoard::Period && !(isPeriodPlaced && type == BoxType::Num)) {
        addNewLetter(".");
        isPeriodPlaced = true;
    }

    if (key == KeyBoard::Backspace) eraseLetter();

    // MSG("UNKNOWN KEY!");
    return EXIT_SUCCESS;
}

int EditBox::onKeyReleased (KeyBoard::Key key) {
    if (key == KeyBoard::LShift) capsLocked = false;

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

    MESSAGE("%lg", SIZE.x / 36);
    if (curString.size() < SIZE.x / 36)
        curString.push_back(*letter);

    return;
}

#define CASE(LETTER, letter)                  \
    case KeyBoard::Key::LETTER:                \
        return (capsLocked? #LETTER : #letter); \
        break;

const char* EditBox::translateLetter(KeyBoard::Key letter) {
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
