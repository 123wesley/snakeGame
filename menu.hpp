#include <SFML/Graphics.hpp>

using namespace sf;

const int MAX_NUMBER_OF_ITEMS = 3;

class Menu
{
public:
    Menu(float width, float height);
    ~Menu();
    
    void draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressItem(){return selectedItemIndex;};

private:
    int selectedItemIndex;
    Font font;
    Text title;
    Text menu [MAX_NUMBER_OF_ITEMS];
    
};
