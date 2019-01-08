#include "menu.hpp"

Menu::Menu(float width, float height)
{
    if(!font.loadFromFile("font.ttf")){
        //handle error
    }
    title.setFont(font);
    title.setFillColor(Color::Cyan);
    title.setString("SNAKE GAME");
    title.setPosition(Vector2f(width / 2 - 160, height / (MAX_NUMBER_OF_ITEMS + 2) * 0.5));
    title.setCharacterSize(60);
    
    menu[0].setFont(font);
    menu[0].setFillColor(Color::Red);
    menu[0].setString("1P Mode");
    menu[0].setPosition(Vector2f(width / 2 - 46, height / (MAX_NUMBER_OF_ITEMS + 2) * 2));

    
    menu[1].setFont(font);
    menu[1].setFillColor(Color::White);
    menu[1].setString("2P Mode");
    menu[1].setPosition(Vector2f(width / 2 - 47, height / (MAX_NUMBER_OF_ITEMS + 2) * 3));
    
    menu[2].setFont(font);
    menu[2].setFillColor(Color::White);
    menu[2].setString("EXIT");
    menu[2].setPosition(Vector2f(width / 2 - 35, height / (MAX_NUMBER_OF_ITEMS + 2) * 4));
    
    selectedItemIndex = 0;
    
};

Menu::~Menu()
{
    
}

void Menu::draw(sf::RenderWindow &window){
    window.draw(title);
    for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
        window.draw(menu[i]);
    }
}

void Menu::MoveUp(){
    if(selectedItemIndex - 1 >= 0){
        menu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex --;
        menu[selectedItemIndex].setFillColor(Color::Red);
    }
    
};
void Menu::MoveDown(){
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS){
        menu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex ++;
        menu[selectedItemIndex].setFillColor(Color::Red);
    }
    
};

