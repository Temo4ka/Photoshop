#include "../Headers/Widgets.h"


Button::Button(Vect pos, Vect size, const char *message, sf::Font *font, sf::Texture *texture, sf::Sprite *sprite, int (*run)(Button *button),
                                                                                                                                const int W, const int H):
Widget(pos, size, texture, W, H, sprite) //base construction
{
    this -> run  = run;
    this -> font = font;
    this -> text = new sf::Text(message, *font);
    this -> text -> setCharacterSize(CharacterSize);
    this -> text -> setPosition(this->getPosition().x + 40, this->getPosition().y + 24);

    this -> status = Released;
}

int Button::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);

    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    // MESSAGE("%s: %d", ((std::string) text->getString()).c_str(), this->getRegionSet()->getSize());

    int square = 0;

    ListNode<Region> *curRegionNode = ((this->getRegionSet())->getHead())->getHead();
    for (int i = 0; i < this->getRegionSet()->getSize(); i++) {
        Region *curRegion = curRegionNode->getObject();

        Vect curPos  = curRegion->getPos();
        Vect curSize = curRegion->getSize();
        Vect  scale  = this -> getScale();

        (this->getSprite())->setTextureRect(sf::IntRect((curPos.x - POSITION.x) / scale.x, BUTTON_PIC_HEIGHT * status + (curPos.y - POSITION.y) / scale.y,
                                                            curSize.x / scale.x, curSize.y / scale.y));

        (this->getSprite())->setPosition(curPos.x, curPos.y);

        (rt->getWindow())->draw(*(this->getSprite()));
        
        curRegionNode = curRegionNode -> getNext();

        square += curSize.x * curSize.y;
    }

    text -> setCharacterSize(CharacterSize);
    
    if (square >= getSizeVect().x * getSizeVect().y / 2)
        (rt->getWindow())->draw(*(this->text));

    return EXIT_SUCCESS;
}

int Button::onMousePress(Vect &mouse) {
    if (!isInWidgetRegion(mouse) || this -> getStatus() == Disable)
        return EXIT_SUCCESS;

    status = Status::Pressed;

    if (run != nullptr) run(this);

    return EXIT_SUCCESS;
}

int Button::onMouseMove(Vect &mouse) {
    if (!isInWidgetRegion(mouse))
        status = Status::Released;

    return EXIT_SUCCESS;
}

int Button::onMouseRelease(Vect &mouse) {
    status = Status::Released;

    return EXIT_SUCCESS;
}

void Button::move(Vect delta) {
    setPosition(POSITION + delta);

    text -> setPosition(text -> getPosition() + sf::Vector2f(delta.x, delta.y));

    return;
}

int Button::clipRegions() {
    return EXIT_SUCCESS;
}

void Button::dumpRegions(sf::RenderWindow *window) {
    this -> getRegionSet() -> dump(window);

    return;
}
