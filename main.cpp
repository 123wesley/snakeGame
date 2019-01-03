#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int N = 30, M = 20, size = 16, w = size * N, h = size * M, Max_Snake_Length = 100, Snake_orig_length = 4;

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

	void Snake_Move();
};
class Fruit
{
private:
	Pos pos;
public:
	Fruit();
	Fruit(const int& x, const int& y);
	~Fruit();
	Pos get_pos();
	void set_pos(const Pos& pos);
	void got_eaten_by(Snake& snake);
};
//////// End of headers

//////// Snake Constructors and Functions
Snake::Snake():dir(0), length(Snake_orig_length)
{
	for (int i = 0; i < Snake_orig_length; i++) {
		this->s[i].x = N/2;
		this->s[i].y = M/2 - i;
	}
}
Snake::Snake(const int& dir, const Pos& pos) : length(Snake_orig_length)
{
	this->dir = dir;

	if (dir == 0){
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
Snake::Snake(const int& dir, const int& x, const int& y) : length(Snake_orig_length)
{
	this->dir = dir;

	if (dir == 0) {
		for (int i = 0; i < Snake_orig_length; i++) {
			this->s[i].x = x;
			this->s[i].y = y - i;
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
			this->s[i].x = x + i;
			this->s[i].y = y;
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
			this->s[i].x = x - i;
			this->s[i].y = y;
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
			this->s[i].x = x;
			this->s[i].y = y + i;
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
	if(dir <= 3 && dir >=0)
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
	if(length <= Max_Snake_Length && length >= Snake_orig_length)
		this->length = length;
}
Pos Snake::get_head_pos()
{
	return this->s[0];
}
void Snake::set_head_pos(const Pos& pos)
{
	this->s[0] = pos;
}
Pos Snake::get_i_pos(const int& i)
{
	return this->s[i];
}

void Snake::Snake_Move()
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

	if (this->s[0].x > N) this->s[0].x = 0;  if (this->s[0].x < 0) this->s[0].x = N;
	if (this->s[0].y > M) this->s[0].y = 0;  if (this->s[0].y < 0) this->s[0].y = M;

	for (int i = 1; i < length; i++)
		if (this->s[0].x == this->s[i].x && this->s[0].y == this->s[i].y)  this->length = i;
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
	this->pos.x = rand() % N;
	this->pos.y = rand() % M;

	int len = snake.get_length();
	len++;
	snake.set_length(len);
}
/////// End of Fruit Constructors and Functions

//Origin
/*
struct Snake
{
	int x, y;
}  s[100];

struct Fruct
{
	int x, y;
} f;

void Tick()
{
	for (int i = num; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	if (dir == 0) s[0].y += 1;
	if (dir == 1) s[0].x -= 1;
	if (dir == 2) s[0].x += 1;
	if (dir == 3) s[0].y -= 1;

	if ((s[0].x == f.x) && (s[0].y == f.y))
	{
		num++;
		f.x = rand() % N;
		f.y = rand() % M;
	}

	if (s[0].x > N) s[0].x = 0;  if (s[0].x < 0) s[0].x = N;
	if (s[0].y > M) s[0].y = 0;  if (s[0].y < 0) s[0].y = M;

	for (int i = 1; i < num; i++)
		if (s[0].x == s[i].x && s[0].y == s[i].y)  num = i;
}
*/
//////////////////// Change end.  By Chien.

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(w, h), "Snake Game!");

	Texture t1, t2;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");

	Sprite sprite1(t1);
	Sprite sprite2(t2);

	Clock clock;
	float timer = 0, delay = 0.1;

	Snake snake(0, 5, 5);
	Fruit fruit(10, 10);
	/*
	f.x = 10;
	f.y = 10;
	*/
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		//////////////////// add "&& dir !=" to forbid player changing to the oppsite direction. By Chien.

		if (Keyboard::isKeyPressed(Keyboard::Left) && snake.get_dir() != 2) snake.set_dir(1);
		if (Keyboard::isKeyPressed(Keyboard::Right) && snake.get_dir() != 1)  snake.set_dir(2);
		if (Keyboard::isKeyPressed(Keyboard::Up) && snake.get_dir() != 0) snake.set_dir(3);
		if (Keyboard::isKeyPressed(Keyboard::Down) && snake.get_dir() != 3) snake.set_dir(0);

		//////////////////// add end. By Chien.

		if (timer > delay)
		{ 
			timer = 0;
			snake.Snake_Move();
			if (snake.get_head_pos().x == fruit.get_pos().x && snake.get_head_pos().y == fruit.get_pos().y) {
				fruit.got_eaten_by(snake);
			}
		}

		////// draw  ///////
		window.clear();

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				sprite1.setPosition(i*size, j*size);
				window.draw(sprite1);
			}

		for (int i = 0; i < snake.get_length(); i++)
		{
			sprite2.setPosition(snake.get_i_pos(i).x*size, snake.get_i_pos(i).y*size);  
			window.draw(sprite2);
		}

		sprite2.setPosition(fruit.get_pos().x*size, fruit.get_pos().y*size);
		window.draw(sprite2);

		window.display();
	}

	return 0;
}
