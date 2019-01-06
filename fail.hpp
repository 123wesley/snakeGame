#include <SFML/Graphics.hpp>
#include "const.hpp"
using namespace sf;

const int MAX_NUMBER_OF_FAILMENU_ITEMS = 2;

class Fail
{
public:
    Fail(float width, float height);
    ~Fail();
    
    void draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressItem(){return selectedItemIndex;};
    
private:
    int selectedItemIndex;
    Font font;
    Sprite gameOver; //game over image
    Text failMenu [MAX_NUMBER_OF_FAILMENU_ITEMS];
    
};
