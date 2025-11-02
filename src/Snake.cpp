#include "Snake.hpp"

Snake::Snake(sf::Texture *texture) : timer(0), maxTimer(30)
{
	this->texture = *texture;
	this->directions.push_back("u");
	this->snake.push_back(
		new Tile(
			this->texture,
			sf::IntRect(sf::Vector2i(0, 3 * 16), sf::Vector2i(16, 16)),
			"head",
			sf::Vector2f(200.f, 600.f),
			this->directions.front()
		)
);
	this->snake.push_back(
		new Tile(
			this->texture,
			sf::IntRect(sf::Vector2i(0, 2 * 16), sf::Vector2i(16, 16)),
			"body",
			sf::Vector2f(this->snake.at(0)->getTilePos().x, this->snake.at(0)->getTilePos().y + 16.f),
			this->directions.front()
		)
	);
	this->snake.push_back(
		new Tile(
			this->texture,
			sf::IntRect(sf::Vector2i(0, 2 * 16), sf::Vector2i(16, 16)),
			"body",
			sf::Vector2f(this->snake.at(1)->getTilePos().x, this->snake.at(1)->getTilePos().y + 16.f),
			this->directions.front()
		)
	);
		this->snake.push_back(
		new Tile(
			this->texture,
			sf::IntRect(sf::Vector2i(0, 2 * 16), sf::Vector2i(16, 16)),
			"body",
			sf::Vector2f(this->snake.at(1)->getTilePos().x, this->snake.at(2)->getTilePos().y + 16.f),
			this->directions.front()
		)
	);
		this->snake.push_back(
		new Tile(
			this->texture,
			sf::IntRect(sf::Vector2i(0, 2 * 16), sf::Vector2i(16, 16)),
			"body",
			sf::Vector2f(this->snake.at(1)->getTilePos().x, this->snake.at(3)->getTilePos().y + 16.f),
			this->directions.front()
		)
	);
	this->snake.push_back(
		new Tile(
			this->texture,
			sf::IntRect(sf::Vector2i(6 * 16, 2 * 16), sf::Vector2i(16, 16)),
			"tail",
			sf::Vector2f(this->snake.at(2)->getTilePos().x, this->snake.at(4)->getTilePos().y + 16.f),
			this->directions.front()
		)
	);
}

Snake::~Snake()
{
}

void Snake::getInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		if (this->directions.back() != "l" && this->directions.back() != "r")
		{
			this->directions.push_back("r");
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		if (this->directions.back() != "d" && this->directions.back() != "u")
		{
			this->directions.push_back("u");
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		if (this->directions.back() != "l" && this->directions.back() != "r")
		{
			this->directions.push_back("l");
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (this->directions.back() != "d" && this->directions.back() != "u")
		{
			this->directions.push_back("d");
		}
	}
}

void Snake::update()
{
	// get input from keyboard
	this->getInput();

	// real update
	std::string temp_1;
	std::string temp_2;
	if (timer > maxTimer)
	{
		for (auto &part : this->snake)
		{
			temp_1 = part->getDir();
			// head
			if (part->getPart() == "head")
			{
				if (part->getDir() != this->directions.front())
				{
					part->handleHead(this->directions.front(), &this->turns, this->texture);
				}
			}
			else
				part->changeDir(temp_2);
			temp_2 = temp_1;

			// actual movement
			part->moveTile();

			// body
			part->handleBody(this->turns);

			// tail
			part->handleTail(&this->turns);
		}
		if (this->directions.size() > 1)
			this->directions.erase(this->directions.begin());
		timer = 0;
	}
	timer++;
}

void Snake::render(sf::RenderTarget &target)
{
	for (auto &part : this->snake)
	{
		bool to_render = false;
		if (this->turns.empty())
			to_render = true;
		else
		{
			for (auto &turn_part : this->turns)
			{
				if (part->getTilePos() == turn_part->getTilePos())
				{
					to_render = false;
					break;
				}
				else
					to_render = true;
			}
		}
		if (to_render)
			part->render(target);
	}
	if (!this->turns.empty())
	{
		for (auto &part : turns)
			part->render(target);
	}
}
