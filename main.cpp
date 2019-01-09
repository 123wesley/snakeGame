#include <SFML/Graphics.hpp>
#include <time.h>
/*
#include "menu.hpp"
#include "fail.hpp"
#include "pause.hpp"
 */
#include "menu.cpp"
#include "fail.cpp"
#include "pause.cpp"
#include <string>
#include <iostream>
using namespace sf;
using namespace std;

const int N = 30, M = 20, Size = 16, BAR_HEIGHT = 5, w = Size * N, h = Size * (M + BAR_HEIGHT), Max_Snake_Length = 100, Snake_orig_length = 4;
const int typeCnt = 2;

//////////////////// Change to class to present.  By Chien.

//////// Headers
struct Pos
{
    int x, y;
};

class Snake
{
    friend class Fruit;
private:
    int dir;
    int length;
    Pos s[Max_Snake_Length];
public:
    Snake();
    Snake(const int& dir, const Pos& pos);
    Snake(const int& dir, const int& x, const int& y);
    Snake(const Snake& orig_s);
    ~Snake();
    int get_dir();
    void set_dir(const int& dir);
    int get_length();
    void set_length(const int& length);
    Pos get_head_pos();
    void set_head_pos(const Pos& pos);
    Pos get_i_pos(const int& i);
    
    bool Snake_Move();
};
class Fruit
{
private:
    Pos pos;
    int type; //different types of fruit: 0. grow 1. grow double 2. shrink
public:
    Fruit();
    Fruit(const int& x, const int& y);
    Fruit(const int& type);
    Fruit(const int& x, const int& y, const int& type);
    ~Fruit();
    Pos get_pos();
    void set_pos(const Pos& pos);
    void got_eaten_by(Snake& snake);
    void change_position();
};

//global function
void Intial_game(Snake& snake, Fruit& fruit);
void P2_Intial_game(Snake& snake, Snake& snake2, Fruit& fruit);

//////// End of headers

//////// Snake Constructors and Functions

Snake::Snake() :dir(0), length(Snake_orig_length)
{
    for (int i = 0; i < Snake_orig_length; i++) {
        this->s[i].x = N / 2;
        this->s[i].y = M / 2 - i;
    }
}
Snake::Snake(const int& dir, const Pos& pos) : length(Snake_orig_length)
{
    this->dir = dir;
    this->set_head_pos(pos);
}
Snake::Snake(const int& dir, const int& x, const int& y) : length(Snake_orig_length)
{
    this->dir = dir;
    Pos tmp;
    tmp.x = x;
    tmp.y = y;
    this->set_head_pos(tmp);
}
Snake::Snake(const Snake& orig_s) : length(Snake_orig_length)
{
    //copy constructor
}
Snake::~Snake()
{
}

int Snake::get_dir()
{
    return this->dir;
}
void Snake::set_dir(const int& dir)
{
    if (dir <= 3 && dir >= 0)
        this->dir = dir;
    else
        this->dir = 0;
}
int Snake::get_length()
{
    return this->length;
}
void Snake::set_length(const int& length)
{
    if (length <= Max_Snake_Length && length >= Snake_orig_length)
        this->length = length;
}
Pos Snake::get_head_pos()
{
    return this->s[0];
}
void Snake::set_head_pos(const Pos& pos)
{
    if (dir == 0) {
        for (int i = 0; i < Snake_orig_length; i++) {
            this->s[i].x = pos.x;
            this->s[i].y = pos.y - i;
            if (this->s[i].x <= 0)
                this->s[i].x += N;
            if (this->s[i].x >= N)
                this->s[i].x -= N;
            if (this->s[i].y <= 0)
                this->s[i].y += M;
            if (this->s[i].y >= M)
                this->s[i].y -= M;
        }
    }
    else if (dir == 1) {
        for (int i = 0; i < Snake_orig_length; i++) {
            this->s[i].x = pos.x + i;
            this->s[i].y = pos.y;
            if (this->s[i].x <= 0)
                this->s[i].x += N;
            if (this->s[i].x >= N)
                this->s[i].x -= N;
            if (this->s[i].y <= 0)
                this->s[i].y += M;
            if (this->s[i].y >= M)
                this->s[i].y -= M;
        }
    }
    else if (dir == 2) {
        for (int i = 0; i < Snake_orig_length; i++) {
            this->s[i].x = pos.x - i;
            this->s[i].y = pos.y;
            if (this->s[i].x <= 0)
                this->s[i].x += N;
            if (this->s[i].x >= N)
                this->s[i].x -= N;
            if (this->s[i].y <= 0)
                this->s[i].y += M;
            if (this->s[i].y >= M)
                this->s[i].y -= M;
        }
    }
    else if (dir == 3) {
        for (int i = 0; i < Snake_orig_length; i++) {
            this->s[i].x = pos.x;
            this->s[i].y = pos.y + i;
            if (this->s[i].x <= 0)
                this->s[i].x += N;
            if (this->s[i].x >= N)
                this->s[i].x -= N;
            if (this->s[i].y <= 0)
                this->s[i].y += M;
            if (this->s[i].y >= M)
                this->s[i].y -= M;
        }
    }
}
Pos Snake::get_i_pos(const int& i)
{
    return this->s[i];
}

bool Snake::Snake_Move()
{
    //move the snake
    for (int i = this->length; i > 0; --i)
    {
        this->s[i].x = this->s[i - 1].x;
        this->s[i].y = this->s[i - 1].y;
    }
    
    if (dir == 0) this->s[0].y += 1;
    if (dir == 1) this->s[0].x -= 1;
    if (dir == 2) this->s[0].x += 1;
    if (dir == 3) this->s[0].y -= 1;
    
    if (this->s[0].x > N - 1) this->s[0].x = 0;
    if (this->s[0].x < 0) this->s[0].x = N - 1;
    if (this->s[0].y > M - 1) this->s[0].y = 0;
    if (this->s[0].y < 0) this->s[0].y = M - 1;
    
    for (int i = 1; i < length; i++)
        if (this->s[0].x == this->s[i].x && this->s[0].y == this->s[i].y)
            return false;
    //this->length = i;
    return true;
}
/////// End of Snake Constructors and Functions

//////// Fruit Constructors and Functions
Fruit::Fruit()
{
    this->pos.x = 0;
    this->pos.y = 0;
}
Fruit::Fruit(const int& x, const int& y)
{
    this->pos.x = x;
    this->pos.y = y;
}
Fruit::Fruit(const int& x, const int& y, const int& type)
{
    this->pos.x = x;
    this->pos.y = y;
    this->type = type;
}
Fruit::Fruit(const int& type) //fruits that hasn't appear
{
    this->pos.x = -1;
    this->pos.y = -1;
    this->type = type;
}
Fruit::~Fruit()
{
}

Pos Fruit::get_pos()
{
    return this->pos;
}
void Fruit::set_pos(const Pos& pos)
{
    this->pos = pos;
}
void Fruit::got_eaten_by(Snake& snake)
{
    int len = snake.get_length();
    if (this->type == 0)
    {
        len++;
        snake.set_length(len);
    }
    else if (this->type == 1)
    {
        len = len + 3;
        snake.set_length(len);
    }
    else if (this->type == 2)
    {
        len = len - 1;
        snake.set_length(len);
    }
    else if (this->type == 3)
    {
        len = len - 3;
        snake.set_length(len);
    }
}
void Fruit::change_position()
{
    this->pos.x = rand() % N;
    this->pos.y = rand() % M;
}

/////// End of Fruit Constructors and Functions

//global function

void P1_Intial_game(Snake& snake, Fruit& fruit) {
    Pos tmp;
    
    tmp.x = 5;
    tmp.y = 5;
    snake.set_dir(0);
    snake.set_length(4);
    snake.set_head_pos(tmp);
    
    tmp.x = 10;
    tmp.y = 10;
    fruit.set_pos(tmp);
}
void P2_Intial_game(Snake& snake, Snake& snake2, Fruit& fruit) {
    Pos tmp;
    
    tmp.x = 5;
    tmp.y = 5;
    snake.set_dir(0);
    snake.set_length(4);
    snake.set_head_pos(tmp);
    
    snake2.set_dir(0);
    snake2.set_length(4);
    tmp.x = N - 5;
    snake2.set_head_pos(tmp);
    
    tmp.x = 10;
    tmp.y = 10;
    fruit.set_pos(tmp);
}


//////////////////// Change end.  By Chien.

int main()
{
    srand(time(0));
    
    RenderWindow window(VideoMode(w, h), "Snake Game!");
    
    Menu menu(window.getSize().x, window.getSize().y);
    Fail fail(window.getSize().x, window.getSize().y);
    RectangleShape bottomBar(Vector2f(w,BAR_HEIGHT*Size));
    bottomBar.setFillColor(Color::Black);
    Pause pause(window.getSize().x, window.getSize().y);
    int gameState = 0; // 0: main menu / 1 : 1p mode / 2 : 2p mode / 3 : 1P mode failure / 4 : 2P mode failure / 5 : 1P pause state / 6 : 2P pause state
    
    Texture t1, t2, t3, t4;// t5;
    t1.loadFromFile("/Users/chihsin1/Desktop/Snake/snakeGameMon/snakeGameMon/images/white.png");
    t2.loadFromFile("/Users/chihsin1/Desktop/Snake/snakeGameMon/snakeGameMon/images/green.png");
    t3.loadFromFile("/Users/chihsin1/Desktop/Snake/snakeGameMon/snakeGameMon/images/game-over.png");
    t4.loadFromFile("/Users/chihsin1/Desktop/Snake/snakeGameMon/snakeGameMon/images/red.png");
    
    Font font;
    font.loadFromFile("/Users/chihsin1/Desktop/Snake/snakeGameMon/snakeGameMon/font.ttf");
    
    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);
    Sprite sprite4(t4);
    
    Clock clock;
    float timer = 0, delay = 0.2;
    int freq = 0;
    
    bool game_start = true;
    
    Snake snake(0, 5, 5);
    Snake snake2(0, N - 5, 5);
    Fruit fruit[typeCnt];
    for (int i = 0; i < typeCnt; i++)
    {
        if (i == 0)
            fruit[i] = Fruit(10, 10, i);
        else
            fruit[i] = Fruit(i);
    }
    
    
    std::string point = "Point: ", p1 = "1P ", p2 = "2P ";
    Text OnePCount;
    OnePCount.setFont(font);
    OnePCount.setFillColor(Color::Cyan);
    OnePCount.setString(point);
    OnePCount.setPosition(Vector2f(10, 10));
    OnePCount.setCharacterSize(30);
    
    Text TwoPCount1, TwoPCount2;
    TwoPCount1.setFont(font);
    TwoPCount2.setFont(font);
    TwoPCount1.setFillColor(Color::Cyan);
    TwoPCount2.setFillColor(Color::Cyan);
    TwoPCount1.setString(p1 + point);
    TwoPCount2.setString(p2 + point);
    TwoPCount1.setPosition(Vector2f(10, 10));
    TwoPCount2.setPosition(Vector2f(w - 180, 10));
    TwoPCount1.setCharacterSize(30);
    TwoPCount2.setCharacterSize(30);
    
    float timeF[typeCnt] = {0};
    bool exist[typeCnt] = {false};
    bool fruitState = false;
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        for (int i = 1; i < typeCnt; i++)
        {
            timeF[i] += time;
        }
        
        
        if (exist[1] == false)
        {
            if (timeF[1] >= 20)
            {
                fruit[1].change_position();
                timeF[1] = 0;
                exist[1] = true;
            }
        }
        else
        {
            if (timeF[1] >= 15)
            {
                fruit[1] = Fruit(1);
                timeF[1] = 0;
                exist[1] = false;
            }
        }
        
        if (exist[2] == false)
        {
            if (timeF[2] >= 10)
            {
                fruit[2].change_position();
                timeF[2] = 0;
                exist[2] = true;
            }
        }
        else
        {
            if (timeF[2] >= 10)
            {
                fruit[2] = Fruit(2);
                timeF[2] = 0;
                exist[2] = false;
            }
        }
        
        if (exist[3] == false)
        {
            if (timeF[3] >= 15)
            {
                fruit[3].change_position();
                timeF[3] = 0;
                exist[3] = true;
            }
        }
        else
        {
            if (timeF[3] >= 15)
            {
                fruit[3] = Fruit(3);
                timeF[3] = 0;
                exist[3] = false;
            }
        }
        
        Event e;
        while (window.pollEvent(e))
        {
            switch (e.type) {
                case Event::Closed:
                    window.close();
                case Event::KeyPressed:
                    if (gameState == 0) { //MENU
                        if (Keyboard::isKeyPressed(Keyboard::Up))
                        {
                            menu.MoveUp();
                            break;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Down))
                        {
                            menu.MoveDown();
                            break;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Return))
                        {
                            if (menu.GetPressItem() == 0)
                            {
                                game_start = true;
                                gameState = 1; // 1P
                                P1_Intial_game(snake, fruit[0]);
                                P2_Intial_game(snake, snake2, fruit[0]);
                            }
                            if (menu.GetPressItem() == 1)
                            {
                                game_start = true;
                                gameState = 2; // 2P
                                P1_Intial_game(snake, fruit[0]);
                                P2_Intial_game(snake, snake2, fruit[0]);
                            }
                            if (menu.GetPressItem() == 2) { window.close(); } // EXIT
                            break;
                        }
                    }
                    
                    if (gameState == 1) { // 1P STATE
                        
                        //////////////////// add "&& dir !=" to forbid player changing to the oppsite direction. By Chien.
                        
                        if (Keyboard::isKeyPressed(Keyboard::Left) && snake.get_dir() != 2) snake.set_dir(1);
                        if (Keyboard::isKeyPressed(Keyboard::Right) && snake.get_dir() != 1)  snake.set_dir(2);
                        if (Keyboard::isKeyPressed(Keyboard::Up) && snake.get_dir() != 0) snake.set_dir(3);
                        if (Keyboard::isKeyPressed(Keyboard::Down) && snake.get_dir() != 3) snake.set_dir(0);
                        //Pause
                        if (Keyboard::isKeyPressed(Keyboard::Space) && game_start == true) {
                            game_start = false;
                            gameState = 5;
                        }
                        
                    }
                    
                    if (gameState == 2) { // 2P STATE
                        
                        if (Keyboard::isKeyPressed(Keyboard::Left) && snake.get_dir() != 2) snake.set_dir(1);
                        if (Keyboard::isKeyPressed(Keyboard::Right) && snake.get_dir() != 1)  snake.set_dir(2);
                        if (Keyboard::isKeyPressed(Keyboard::Up) && snake.get_dir() != 0) snake.set_dir(3);
                        if (Keyboard::isKeyPressed(Keyboard::Down) && snake.get_dir() != 3) snake.set_dir(0);
                        
                        if (Keyboard::isKeyPressed(Keyboard::A) && snake2.get_dir() != 2) snake2.set_dir(1);
                        if (Keyboard::isKeyPressed(Keyboard::D) && snake2.get_dir() != 1) snake2.set_dir(2);
                        if (Keyboard::isKeyPressed(Keyboard::W) && snake2.get_dir() != 0) snake2.set_dir(3);
                        if (Keyboard::isKeyPressed(Keyboard::S) && snake2.get_dir() != 3) snake2.set_dir(0);
                        //Pause
                        if (Keyboard::isKeyPressed(Keyboard::Space) && game_start == true) {
                            game_start = false;
                            gameState = 6;
                        }
                        
                        //////////////////// add end. By Chien.
                    }
                    
                    if (gameState == 3 || gameState == 4) { //1p & 2p Failmenu
                        if (Keyboard::isKeyPressed(Keyboard::Up))
                        {
                            fail.MoveUp();
                            break;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Down))
                        {
                            fail.MoveDown();
                            break;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Return))
                        {
                            if (fail.GetPressItem() == 0)
                            {
                                game_start = true;
                                gameState = 0;
                            }
                            
                            if (fail.GetPressItem() == 1) { window.close(); } // EXIT
                            break;
                        }
                    }
                    
                    if (gameState == 5 || gameState == 6) { //Pause state 1P & 2P
                        if (Keyboard::isKeyPressed(Keyboard::Up))
                        {
                            pause.MoveUp();
                            break;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Down))
                        {
                            pause.MoveDown();
                            break;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Return))
                        {
                            if (pause.GetPressItem() == 0 && gameState == 5)
                            {
                                game_start = true;
                                gameState = 1;
                            }
                            
                            if (pause.GetPressItem() == 0 && gameState == 6)
                            {
                                game_start = true;
                                gameState = 2;
                            }
                            
                            if (pause.GetPressItem() == 1) {
                                gameState = 0;
                            } // main menu
                            break;
                        }
                    }
                    break;
            }
        }
        
        
        
        if (timer > delay && game_start)
        {
            if (snake.Snake_Move() && snake2.Snake_Move()) {
                timer = 0;
                for (int i = 0; i < typeCnt; i++)
                {
                    if (snake.get_head_pos().x == fruit[i].get_pos().x && snake.get_head_pos().y == fruit[i].get_pos().y)
                    {
                        fruit[i].got_eaten_by(snake);
                        if (i == 0)
                            fruit[i].change_position();
                        else
                        {
                            fruit[i] = Fruit(i);
                            exist[i] = false;
                            timeF[i] = 0;
                        }
                    }
                    if (snake2.get_head_pos().x == fruit[i].get_pos().x && snake2.get_head_pos().y == fruit[i].get_pos().y)
                    {
                        fruit[i].got_eaten_by(snake2);
                        if (i == 0)
                            fruit[i].change_position();
                        else
                        {
                            fruit[i] = Fruit(i);
                            exist[i] = false;
                            timeF[i] = 0;
                        }
                    }
                }
            }
            else
            {
                game_start = false;
            }
            freq ++;
            if (freq == 20)
            {
                if (delay >= 0.08)
                {
                    delay = delay - 0.01;
                    cout << delay << " ";
                }
                freq = 0;
            }
        }
        
        
        ////// draw  ///////
        window.clear();
        
        // menu state
        if (gameState == 0)
            menu.draw(window);
        
        
        //game state 1P & fail state 1P & 1P pause state
        if (gameState == 1 || gameState == 3 || gameState == 5) {
            
            Vertex line1[] =
            {
                Vertex(Vector2f(0, BAR_HEIGHT*Size)),
                Vertex(Vector2f(N*Size, BAR_HEIGHT*Size))
            };
            Vertex line2[] =
            {
                Vertex(Vector2f(0, BAR_HEIGHT*Size)),
                Vertex(Vector2f(0, M*Size + BAR_HEIGHT*Size))
            };
            Vertex line3[] =
            {
                Vertex(Vector2f(0, M*Size + BAR_HEIGHT*Size)),
                Vertex(Vector2f(N*Size, M*Size + BAR_HEIGHT*Size))
            };
            Vertex line4[] =
            {
                Vertex(Vector2f(N*Size, M*Size + BAR_HEIGHT*Size)),
                Vertex(Vector2f(N*Size, BAR_HEIGHT*Size))
            };
            
            window.draw(line1, 2, Lines);
            window.draw(line2, 2, Lines);
            window.draw(line3, 2, Lines);
            window.draw(line4, 2, Lines);
            
            std::string pnum = to_string(snake.get_length() - 4);
            OnePCount.setString(p1 + point + pnum);
            window.draw(OnePCount);
            
            for (int i = 0; i < snake.get_length(); i++)
            {
                sprite2.setPosition(snake.get_i_pos(i).x*Size, (snake.get_i_pos(i).y + BAR_HEIGHT)*Size);
                window.draw(sprite2);
            }
            
            sprite4.setPosition(fruit[0].get_pos().x*Size, (fruit[0].get_pos().y + BAR_HEIGHT)*Size);
            window.draw(sprite4);
            
            sprite2.setPosition(fruit[2].get_pos().x*Size, (fruit[2].get_pos().y + BAR_HEIGHT)*Size);
            window.draw(sprite2);
            
            if (fruitState == true)
            {
                sprite4.setPosition(fruit[1].get_pos().x*Size, (fruit[1].get_pos().y + BAR_HEIGHT)*Size);
                window.draw(sprite4);
                fruitState = false;
            }
            else
            {
                sprite2.setPosition(fruit[3].get_pos().x*Size, (fruit[3].get_pos().y + BAR_HEIGHT)*Size);
                window.draw(sprite2);
                fruitState = true;
            }
           
            //Pause
            if(gameState == 5){
                pause.draw(window);
            }
            
            
            // GameOver
            if (!game_start && gameState != 5) {
                for (int i = 0; i < N; i++)
                    for (int j = BAR_HEIGHT; j < M + BAR_HEIGHT; j++)
                    {
                        sprite1.setPosition(i*Size, j*Size);
                        window.draw(sprite1);
                    }
                gameState = 3;
                sprite3.setPosition(w / 2 - 175, -30);
                window.draw(sprite3);
                bottomBar.setPosition(0,h - (BAR_HEIGHT * Size));
                window.draw(bottomBar);
                fail.draw(window);
            }
        }
        
        //game state 2P & fail state 2P
        if (gameState == 2 ||  gameState == 4 || gameState == 6) {
            
            Vertex line1[] =
            {
                Vertex(Vector2f(0, BAR_HEIGHT*Size)),
                Vertex(Vector2f(N*Size, BAR_HEIGHT*Size))
            };
            Vertex line2[] =
            {
                Vertex(Vector2f(0, BAR_HEIGHT*Size)),
                Vertex(Vector2f(0, M*Size + BAR_HEIGHT*Size))
            };
            Vertex line3[] =
            {
                Vertex(Vector2f(0, M*Size + BAR_HEIGHT*Size)),
                Vertex(Vector2f(N*Size, M*Size + BAR_HEIGHT*Size))
            };
            Vertex line4[] =
            {
                Vertex(Vector2f(N*Size, M*Size + BAR_HEIGHT*Size)),
                Vertex(Vector2f(N*Size, BAR_HEIGHT*Size))
            };
            
            window.draw(line1, 2, Lines);
            window.draw(line2, 2, Lines);
            window.draw(line3, 2, Lines);
            window.draw(line4, 2, Lines);
            
            std::string p1num = to_string(snake.get_length() - 4), p2num = to_string(snake2.get_length() - 4);
            TwoPCount1.setString(p1 + point + p1num);
            TwoPCount2.setString(p2 + point + p2num);
            window.draw(TwoPCount1);
            window.draw(TwoPCount2);
            
            for (int i = 0; i < snake.get_length(); i++)
            {
                sprite2.setPosition(snake.get_i_pos(i).x*Size, (snake.get_i_pos(i).y + BAR_HEIGHT)*Size);
                window.draw(sprite2);
            }
            for (int i = 0; i < snake2.get_length(); i++)
            {
                sprite2.setPosition(snake2.get_i_pos(i).x*Size, (snake2.get_i_pos(i).y + BAR_HEIGHT)*Size);
                window.draw(sprite2);
            }
            
            sprite4.setPosition(fruit[0].get_pos().x*Size, (fruit[0].get_pos().y + BAR_HEIGHT)*Size);
            window.draw(sprite4);
            
            sprite2.setPosition(fruit[2].get_pos().x*Size, (fruit[2].get_pos().y + BAR_HEIGHT)*Size);
            window.draw(sprite2);
            
            if (fruitState == true)
            {
                sprite4.setPosition(fruit[1].get_pos().x*Size, (fruit[1].get_pos().y + BAR_HEIGHT)*Size);
                window.draw(sprite4);
                fruitState = false;
            }
            else
            {
                sprite2.setPosition(fruit[3].get_pos().x*Size, (fruit[3].get_pos().y + BAR_HEIGHT)*Size);
                window.draw(sprite2);
                fruitState = true;
            }
            
            
            //Pause
            if(gameState == 6){
                pause.draw(window);
            }
            
            // GameOver
            if (!game_start && gameState != 6) {
                for (int i = 0; i < N; i++)
                    for (int j = BAR_HEIGHT; j < M + BAR_HEIGHT; j++)
                    {
                        sprite1.setPosition(i*Size, j*Size);
                        window.draw(sprite1);
                    }
                gameState = 4;
                sprite3.setPosition(w / 2 - 175, -30);
                window.draw(sprite3);
                bottomBar.setPosition(0,h - (BAR_HEIGHT * Size));
                window.draw(bottomBar);
                fail.draw(window);
            }
        }
        
     
            
        
        window.display();
    }
    delay = 0.2;
    
    return 0;
}
