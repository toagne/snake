#ifndef GAME_H
#define GAME_H

#include "Snake.hpp"

class Game
{
private:
	sf::RenderWindow window;
	sf::Texture snakeTexture;
	Snake *snake;

	void update();
	void render();
public:
	Game();
	~Game();

	void run();
};

#endif