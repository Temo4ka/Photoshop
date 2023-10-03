#include "../Headers/Widgets.h"

Button::Button(Vect &pos, Vect &size, const char *message, sf::Font *font) {
    Widget(pos, size);

    this -> text = sf::Text(message, *font);
    this -> text.setCharacterSize(15);
    this -> text.setPosition(this->position.x, this -> position.y);
}

int Window::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);

    if (this -> status == Disable) return EXIT_SUCCESS;

    (rt->window)->draw(*(this->getSprite()));

    ListNode* cur = (this -> getList()).getHead();

    if (cur == nullptr) return EXIT_SUCCESS;
    
    do {
        (cur -> getObject()) -> draw();
        cur = cur -> getNext();
    } while (cur != (this -> getList()).getHead())

    return EXIT_SUCCESS;
}

int Menu::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);

    if (this -> status == Disable) return EXIT_SUCCESS;

    do {
        (cur -> getObject()) -> draw();
        cur = cur -> getNext();
    } while (cur != (this -> getList()).getHead())

    return EXIT_SUCCESS;
}

int Button::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);

    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    (rt->window)->draw(*(this->getSprite()));

    return EXIT_SUCCESS;
}