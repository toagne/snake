#include "Game.hpp"

void Game::update()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
	}

	this->snake->update();
}

void Game::render()
{
	this->window.clear();

	this->snake->render(this->window);

	this->window.display();
}

Game::Game()
{
	this->window.create(sf::VideoMode({800u, 800u}), "my_snake", sf::Style::Close);
	window.setFramerateLimit(144);
	if (!snakeTexture.loadFromFile("res/Snake.png"))
		std::cerr << "error loading snake texture" << "\n";
	this->snake = new Snake(&this->snakeTexture);
}

Game::~Game()
{
}

void Game::run()
{
	while (this->window.isOpen())
	{
		this->update();
		this->render();
	}
}
