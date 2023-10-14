#include "../Headers/Widgets.h"

int Canvas::onMouseClick(Vect &mouse) {
    if (POSITION.x > mouse.x || POSITION.x + SIZE.x < mouse.x ||
        POSITION.y > mouse.y || POSITION.y + SIZE.y < mouse.y )
        return EXIT_SUCCESS;
    
    status = Status::Hold;

    tm.p(texture, texture, mouse);

    return EXIT_SUCCESS;
}

int Canvas::onMouseMove(Vect &mouse) {
    if (POSITION.x > mouse.x || POSITION.x + SIZE.x < mouse.x ||
        POSITION.y > mouse.y || POSITION.y + SIZE.y < mouse.y )
    {
        status = Status::Released;
        return EXIT_SUCCESS;
    }

    if (status == Status::Released) return EXIT_SUCCESS;

    tm.m(texture, texture, mouse - POSITION);

    // switch (tool) {
    //     case Tool::Pen: {
    //         sf::RectangleShape point(sf::Vector2f(3, 3));
    //         point.setPosition(mouse.x - POSITION.x, mouse.y - POSITION.y);
    //         point.setFillColor(color);
    //         texture->draw(point);
    //     }
    //     break;
        
    //     case Tool::Brush: {
    //         sf::CircleShape point(8);
    //         point.setPosition(mouse.x - POSITION.x, mouse.y - POSITION.y);
    //         point.setFillColor(color);
    //         texture->draw(point);
    //     }
    //     break;
        
    //     case Tool::Rubber: {
    //         sf::CircleShape point(8);
    //         point.setPosition(mouse.x - POSITION.x, mouse.y - POSITION.y);
    //         point.setFillColor(sf::Color(0, 0, 0, 0));
    //         texture->draw(point);
    //     }
    //     break;
        
    //     default: break;
    // }
  
    return EXIT_SUCCESS;
}

int Canvas::onMouseReleased(Vect &mouse) {
    status = Status::Released;

    tm.r(texture, texture, mouse);

    return EXIT_SUCCESS;
}

int Canvas::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);
    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    sf::Sprite sprite = {};
    texture -> display();
    sprite.setTexture(texture -> getTexture());

    ListNode<Region> *curRegionNode = ((this->getRegionSet())->getHead())->getHead();
    for (int i = 0; i < this->getRegionSet()->getSize(); i++) {
        Region *curRegion = curRegionNode->getObject();

        Vect curPos  = curRegion->getPos();
        Vect curSize = curRegion->getSize();

        sprite.setTextureRect(sf::IntRect(curPos.x - POSITION.x, curPos.y - POSITION.y, curSize.x, curSize.y));

        sprite.setPosition(curPos.x, curPos.y);

        (rt->getWindow())->draw(sprite);

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