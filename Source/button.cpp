#include "../Headers/Widgets.h"


Button::Button(Vect pos, Vect size, const char *message, sf::Font *font, sf::Texture *texture, sf::Sprite *sprite, int (*run)(Button *button)):
Widget(pos, size, texture, BUTTON_PIC_WIDTH, BUTTON_PIC_HEIGHT, sprite) //base construction
{
    this -> run  = run;
    this -> font = font;
    this -> text = new sf::Text(message, *font);
    this -> text -> setCharacterSize(15);
    this -> text -> setPosition(this->getPosition().x + 40, this->getPosition().y + 24);

    this -> status = Released;
}

int Button::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);

    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    (this->getSprite())->setTextureRect(sf::IntRect(0, BUTTON_PIC_HEIGHT * status, BUTTON_MENU_WIDTH, BUTTON_PIC_HEIGHT));

    (rt->getWindow())->draw(*(this->getSprite()));
    (rt->getWindow())->draw(*(this->text));

    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        (cur -> getObject()) -> draw(rt);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

int Button::onMouseClick(Vect &mouse) {

    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur != nullptr) {
        do {
            catchNullptr(cur -> getObject(), EXIT_FAILURE);
            (cur -> getObject()) -> onMouseClick(mouse);

            cur = cur -> getNext();
        } while (cur != (this -> getList()) -> getHead());
    }

    if (POSITION.x > mouse.x || POSITION.x + SIZE.x < mouse.x ||
        POSITION.y > mouse.y || POSITION.y + SIZE.y < mouse.y || this -> getStatus() == Disable)
        return EXIT_SUCCESS;

    status = Status::Pressed;

    if (run != nullptr) run(this);

    return EXIT_SUCCESS;
}

int Button::onMouseMove(Vect &mouse) {
    if (POSITION.x > mouse.x || POSITION.x + SIZE.x < mouse.x ||
        POSITION.y > mouse.y || POSITION.y + SIZE.y < mouse.y )
        status = Status::Released;

    return EXIT_SUCCESS;
}

int Button::onMouseReleased(Vect &mouse) {
    status = Status::Released;

    return EXIT_SUCCESS;
}