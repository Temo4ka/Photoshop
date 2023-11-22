#include "Widgets.h"
#include <string>

class EditBox : public Window {
    std::string curString;

    sf::Font *font;

    bool capsLocked;

    bool isWriting;

    bool isPeriodPlaced;

    enum BoxType {
        Text = 0,
        Num  = 1
    } type;

    public:

        EditBox(Vect pos, Vect size, sf::Texture *texture, const signed texW, const signed texH, sf::Sprite *sprite):
        Window(pos, size, texture, texW, texH, sprite),
          curString   (std::string()),
          capsLocked  (false),
          isWriting   (false),
        isPeriodPlaced(false),
        font(new sf::Font()),
        type(BoxType::Num)
        {
            font->loadFromFile("./Font/arial.ttf");
            setPriority(HIGH_PRIORITY);
        }

        void addNewLetter(const char *letter);
        void  eraseLetter();

        const char* translateLetter(KeyBoard::Key letter); 

        int draw(RenderTarget *rt);

        int   onMouseMove  (Vect &pos);
        int  onMousePress  (Vect &pos);
        int onMouseRelease(Vect &pos);

        int onKeyPressed (KeyBoard::Key key);
        int onKeyReleased(KeyBoard::Key key);

        void setType(BoxType newType) { type = newType; }
};
