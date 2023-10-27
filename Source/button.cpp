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

    // MESSAGE("%s: %d", ((std::string) text->getString()).c_str(), this->getRegionSet()->getSize());

    ListNode<Region> *curRegionNode = ((this->getRegionSet())->getHead())->getHead();
    for (int i = 0; i < this->getRegionSet()->getSize(); i++) {
        Region *curRegion = curRegionNode->getObject();

        Vect curPos  = curRegion->getPos();
        Vect curSize = curRegion->getSize();
        Vect  scale  = this -> getScale();

        (this->getSprite())->setTextureRect(sf::IntRect(curPos.x - POSITION.x, BUTTON_PIC_HEIGHT * status + curPos.y - POSITION.y,
                                                            curSize.x / scale.x, curSize.y / scale.y));

        (this->getSprite())->setPosition(curPos.x, curPos.y);

        (rt->getWindow())->draw(*(this->getSprite()));
        
        curRegionNode = curRegionNode -> getNext();
    }

    (rt->getWindow())->draw(*(this->text));

    return EXIT_SUCCESS;
}

int Button::onMouseClick(Vect &mouse) {
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

int Button::clipRegions() {
    return EXIT_SUCCESS;
}

void Button::dumpRegions(sf::RenderWindow *window) {
    this -> getRegionSet() -> dump(window);

    return;
}
