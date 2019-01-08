#include <SFML/Graphics.hpp>
using namespace sf;

const int MAX_NUMBER_OF_PAUSEMENU_ITEMS = 2;

class Pause
{
public:
    Pause(float width, float height);
    ~Pause();
    
    void draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressItem(){return selectedItemIndex;};
    
private:
    int selectedItemIndex;
    RectangleShape pauseMenuBackground;
    Font font;
    Text pauseMenu [MAX_NUMBER_OF_PAUSEMENU_ITEMS];
    
};
