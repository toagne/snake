#ifndef SNAKE_H
#define SNAKE_H

#include "Tile.hpp"

class Snake
{
private:
	sf::Texture texture;

	std::vector<Tile*> snake;
	std::vector<Tile*> turns;

	std::vector<std::string> directions;

	unsigned timer;
	unsigned maxTimer;
public:
	Snake(sf::Texture *texture);
	~Snake();

	void getInput();

	void handleHeadTurning(Tile *head);

	void update();
	void render(sf::RenderTarget &target);
};

#endif