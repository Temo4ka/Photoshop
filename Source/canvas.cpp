#include "../Headers/Widgets.h"
#include "../Headers/UI.h"

Canvas::Canvas(Vect pos, Vect size, HostApp *app):
        Widget(pos, size, nullptr, 0, 0, nullptr),
        status(Released),
           texture   (new RenderTarget(pos, size)),
            temp     (new RenderTarget(pos, size)),
         app (app)
        { 
            texture->clear(plugin::Color(255, 255, 255, 255));
            app->toolManager -> tool = new Circle;

            app->filterManager -> lastFilter = new ReverseFilter;
        }

void Canvas::setTool(ToolI *tool) { 
    delete app->toolManager -> tool;
    app->toolManager -> tool = tool;
}

void Canvas::setFilter(plugin::FilterI *filter) { 
    delete app->filterManager -> lastFilter;

    app->filterManager -> lastFilter = filter;
    activateFilter();
}

void Canvas::activateFilter() { app->filterManager -> active = true; }

void Canvas::setColor(sf::Color newColor) { app->toolManager -> color = { newColor.r, newColor.g, newColor.b, newColor.a }; }

int Canvas::onMousePress(Vect &mouse) {
    if (getStatus() == Disable) return EXIT_SUCCESS;
    
    if (!isInWidgetRegion(mouse))
        return EXIT_SUCCESS;

    app -> mainCanvas = this;
    
    if (app->filterManager -> active) {
        app->filterManager -> curRenderTarget = texture;
        app->filterManager -> applyFilter();

        app->filterManager -> active = false;
        return EXIT_SUCCESS;
    }

    status = Status::Hold;

    Vect curPos = mouse - POSITION;
    plugin::MouseContext context = {{curPos.x, curPos.y}, plugin::MouseButton::Left};

    app->toolManager -> paintOnPress(texture, temp, context);

    return EXIT_SUCCESS;
}

int Canvas::onMouseMove(Vect &mouse) {
    if (getStatus() == Disable) return EXIT_SUCCESS;

    if (!isInWidgetRegion(mouse)) {
        status = Status::Released;
        
        return EXIT_SUCCESS;
    }

    // if (status == Status::Released) return EXIT_SUCCESS;

    // temp->create(THIS_SIZE.x, THIS_SIZE.y);

    Vect curPos = mouse - POSITION;
    plugin::MouseContext context = {{curPos.x, curPos.y}, plugin::MouseButton::Left};

    app->toolManager -> paintOnMove(texture, temp, context);
  
    return EXIT_SUCCESS;
}

int Canvas::onMouseRelease(Vect &mouse) {
    if (getStatus() == Disable) return EXIT_SUCCESS;

    status = Status::Released;

    Vect curPos = mouse - POSITION;
    plugin::MouseContext context = {{curPos.x, curPos.y}, plugin::MouseButton::Left};

    app->toolManager -> paintOnRelease(texture, temp, context);

    return EXIT_SUCCESS;
}

int Canvas::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);
    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    sf::Sprite   sprite   = {};
    sf::Sprite tempSprite = {};
    
    texture -> display();
      temp  -> display();

      sprite  .setTexture(texture->getWindow()->getTexture());
    tempSprite.setTexture(  temp ->getWindow()->getTexture());

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