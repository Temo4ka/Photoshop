#include "../Headers/Widgets.h"

Button::Button(Vect pos, Vect size, const char *message, sf::Font *font, sf::Texture *texture, sf::Sprite *sprite):
Widget(pos, size, texture, sprite) //base construction
{
    this -> font = font;
    this -> text = new sf::Text(message, *font);
    this -> text -> setCharacterSize(15);
    this -> text -> setPosition(this->getPosition().x + 40, this->getPosition().y + 24);
}

int Window::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);
    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    (rt->getWindow())->draw(*(this->getSprite()));

    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    catchNullptr(cur, EXIT_FAILURE);

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        (cur -> getObject()) -> draw(rt);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

int Menu::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);

    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    catchNullptr(cur, EXIT_FAILURE);

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        (cur -> getObject()) -> draw(rt);

        cur = cur -> getNext();
        // fprintf(log, "%p Here!!!\n", cur);
        
    } while (cur != (this -> getList()) -> getHead());

    // fclose(log);

    return EXIT_SUCCESS;
}

int Button::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);

    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    (rt->getWindow())->draw(*(this->getSprite()));
    (rt->getWindow())->draw(*(this->text));

    return EXIT_SUCCESS;
}