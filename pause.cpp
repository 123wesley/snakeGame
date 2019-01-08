#include "pause.hpp"


Pause::Pause(float width, float height)
{
    if(!font.loadFromFile("font.ttf")){
        //handle error
    }
    Color gray(26,19,19,230);
    pauseMenuBackground.setFillColor(gray);
    pauseMenuBackground.setSize(Vector2f(width / 3,height / 2.5));
    pauseMenuBackground.setPosition(width/8 * 2 + 40, height / 2.4);
    
    pauseMenu[0].setFont(font);
    pauseMenu[0].setFillColor(Color::Red);
    pauseMenu[0].setString("RESUME");
    pauseMenu[0].setPosition(Vector2f(width / 2 - 48, height / (MAX_NUMBER_OF_PAUSEMENU_ITEMS+ 4) * 3));
    

    pauseMenu[1].setFont(font);
    pauseMenu[1].setFillColor(Color::White);
    pauseMenu[1].setString("MENU");
    pauseMenu[1].setPosition(Vector2f(width / 2 - 37, height / (MAX_NUMBER_OF_PAUSEMENU_ITEMS + 4) * 4));
    
    
    
    selectedItemIndex = 0;
    
};

Pause::~Pause()
{
    
}

void Pause::draw(sf::RenderWindow &window){
    window.draw(pauseMenuBackground);
    for(int i = 0; i < MAX_NUMBER_OF_PAUSEMENU_ITEMS; i++){
        window.draw(pauseMenu[i]);
    }
}

void Pause::MoveUp(){
    if(selectedItemIndex - 1 >= 0){
        pauseMenu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex --;
        pauseMenu[selectedItemIndex].setFillColor(Color::Red);
    }
    
};
void Pause::MoveDown(){
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_PAUSEMENU_ITEMS){
        pauseMenu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex ++;
        pauseMenu[selectedItemIndex].setFillColor(Color::Red);
    }
    
};

