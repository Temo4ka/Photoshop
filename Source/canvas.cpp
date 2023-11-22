#include "../Headers/Widgets.h"

int Canvas::onMousePress(Vect &mouse) {
    if (!isInWidgetRegion(mouse))
        return EXIT_SUCCESS;
    
    if (filterManager -> active) {
        filterManager -> apply(texture);

        filterManager -> active = false;
        return EXIT_SUCCESS;
    }

    status = Status::Hold;

    toolManager -> onMousePressed(texture, temp, mouse - POSITION);

    return EXIT_SUCCESS;
}

int Canvas::onMouseMove(Vect &mouse) {
    if (!isInWidgetRegion(mouse)) {
        status = Status::Released;
        
        return EXIT_SUCCESS;
    }

    // if (status == Status::Released) return EXIT_SUCCESS;

    temp->create(SIZE.x, SIZE.y);
    temp->clear(sf::Color(0, 0, 0, 0));
    toolManager -> onMouseMove(texture, temp, mouse - POSITION);
  
    return EXIT_SUCCESS;
}

int Canvas::onMouseRelease(Vect &mouse) {
    status = Status::Released;

    toolManager -> onMouseRelease(texture, temp, mouse - POSITION);

    return EXIT_SUCCESS;
}

int Canvas::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);
    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    sf::Sprite   sprite   = {};
    sf::Sprite tempSprite = {};
    
    texture -> display();
      temp  -> display();

      sprite  .setTexture(texture -> getTexture());
    tempSprite.setTexture(  temp  -> getTexture());

    ListNode<Region> *curRegionNode = ((this->getRegionSet())->getHead())->getHead();
    for (int i = 0; i < this->getRegionSet()->getSize(); i++) {
        Region *curRegion = curRegionNode->getObject();

        Vect curPos  = curRegion->getPos();
        Vect curSize = curRegion->getSize();
        // Vect  scale  = this -> getScale();

        sprite.setTextureRect(sf::IntRect(curPos.x - POSITION.x, curPos.y - POSITION.y, curSize.x, curSize.y));
        tempSprite.setTextureRect(sf::IntRect(curPos.x - POSITION.x, curPos.y - POSITION.y, curSize.x, curSize.y));

        sprite.setPosition(curPos.x, curPos.y);
        tempSprite.setPosition(curPos.x, curPos.y);

        (rt->getWindow())->draw(  sprite  );
        (rt->getWindow())->draw(tempSprite);

        curRegionNode = curRegionNode -> getNext();
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