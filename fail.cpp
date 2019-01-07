
#include "fail.hpp"

Fail::Fail(float width, float height)
{
    if(!font.loadFromFile("font.ttf")){
        //handle error
    }
    
    failMenu[0].setFont(font);
    failMenu[0].setFillColor(Color::Red);
    failMenu[0].setString("MENU");
    failMenu[0].setPosition(Vector2f(width / 2 - 46, height / (MAX_NUMBER_OF_FAILMENU_ITEMS+ 8) * 8));
    
    
    failMenu[1].setFont(font);
    failMenu[1].setFillColor(Color::White);
    failMenu[1].setString("EXIT");
    failMenu[1].setPosition(Vector2f(width / 2 - 42, height / (MAX_NUMBER_OF_FAILMENU_ITEMS + 8) * 9));
    

    
    selectedItemIndex = 0;
    
};

Fail::~Fail()
{
    
}

void Fail::draw(sf::RenderWindow &window){
    //window.draw(gameOver);
    for(int i = 0; i < MAX_NUMBER_OF_FAILMENU_ITEMS; i++){
        window.draw(failMenu[i]);
    }
}

void Fail::MoveUp(){
    if(selectedItemIndex - 1 >= 0){
        failMenu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex --;
        failMenu[selectedItemIndex].setFillColor(Color::Red);
    }
    
};
void Fail::MoveDown(){
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_FAILMENU_ITEMS){
        failMenu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex ++;
        failMenu[selectedItemIndex].setFillColor(Color::Red);
    }
    
};


