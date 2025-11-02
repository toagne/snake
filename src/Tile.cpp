#include "Tile.hpp"

Tile::Tile(sf::Texture &texture, sf::IntRect rect, std::string part, sf::Vector2f pos, std::string dir)
	: sprite(texture), part(part), dir(dir)
{
	this->sprite.setTextureRect(rect);
	this->sprite.setPosition(pos);
}

Tile::~Tile()
{
}

const std::string &Tile::getPart() const
{
	return this->part;
}

const std::string &Tile::getDir() const
{
	return this->dir;
}

void Tile::changeDir(std::string newDir)
{
	this->dir = newDir;
}

void Tile::moveTile()
{
	if (this->dir ==  "u")
	{
		this->sprite.move(sf::Vector2f(0.f, -16.f));
	}
	else if (this->dir == "r")
	{
		this->sprite.move(sf::Vector2f(16.f, 0.f));
	}
	else if (this->dir == "d")
	{
		this->sprite.move(sf::Vector2f(0.f, 16.f));
	}
	else if (this->dir == "l")
	{
		this->sprite.move(sf::Vector2f(-16.f, 0.f));
	}
}

void Tile::handleHead(std::string newDir, std::vector<Tile*> *turns, sf::Texture &texture)
{
	if (newDir == "r")
	{
		if (this->dir == "u")
		{
			turns->push_back(
				new Tile(
					texture,
					sf::IntRect(sf::Vector2i(5 * 16, 2 * 16),sf::Vector2i(16, 16)),
					"corner",
					sf::Vector2f(this->sprite.getPosition()),
					newDir
				)
			);
		}
		else if (this->dir == "d")
		{
			turns->push_back(
				new Tile(
					texture,
					sf::IntRect(sf::Vector2i(3 * 16, 2 * 16),sf::Vector2i(16, 16)),
					"corner",
					sf::Vector2f(this->sprite.getPosition()),
					newDir
				)
			);
		}
		this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 6 * 16), sf::Vector2i(16, 16)));
		this->dir = newDir;
	}
	else if (newDir == "l")
	{
		if (this->dir == "u")
		{
			turns->push_back(
				new Tile(
					texture,
					sf::IntRect(sf::Vector2i(4 * 16, 2 * 16),sf::Vector2i(16, 16)),
					"corner",
					sf::Vector2f(this->sprite.getPosition()),
					newDir
				)
			);
		}
		else if (this->dir == "d")
		{
			turns->push_back(
				new Tile(
					texture,
					sf::IntRect(sf::Vector2i(2 * 16, 2 * 16),sf::Vector2i(16, 16)),
					"corner",
					sf::Vector2f(this->sprite.getPosition()),
					newDir
				)
			);
		}
		this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 4 * 16), sf::Vector2i(16, 16)));
		this->dir = newDir;
	}
	else if (newDir == "d")
	{
		if (this->dir == "l")
		{
			turns->push_back(
				new Tile(
					texture,
					sf::IntRect(sf::Vector2i(5 * 16, 2 * 16),sf::Vector2i(16, 16)),
					"corner",
					sf::Vector2f(this->sprite.getPosition()),
					newDir
				)
			);
		}
		else if (this->dir == "r")
		{
			turns->push_back(
				new Tile(
					texture,
					sf::IntRect(sf::Vector2i(4 * 16, 2 * 16),sf::Vector2i(16, 16)),
					"corner",
					sf::Vector2f(this->sprite.getPosition()),
					newDir
				)
			);
		}
		this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 5 * 16), sf::Vector2i(16, 16)));
		this->dir = newDir;
	}
	else if (newDir == "u")
	{
		if (this->dir == "l")
		{
			turns->push_back(
				new Tile(
					texture,
					sf::IntRect(sf::Vector2i(3 * 16, 2 * 16),sf::Vector2i(16, 16)),
					"corner",
					sf::Vector2f(this->sprite.getPosition()),
					newDir
				)
			);
		}
		else if (this->dir == "r")
		{
			turns->push_back(
				new Tile(
					texture,
					sf::IntRect(sf::Vector2i(2 * 16, 2 * 16),sf::Vector2i(16, 16)),
					"corner",
					sf::Vector2f(this->sprite.getPosition()),
					newDir
				)
			);
		}
		this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 3 * 16), sf::Vector2i(16, 16)));
		this->dir = newDir;
	}
}

void Tile::handleBody(std::vector<Tile*> &turns)
{
	if (this->part == "body" && !turns.empty())
	{
		for (auto &turn_part : turns)
		{
			if (this->sprite.getPosition() == turn_part->getTilePos())
			{
				if (this->dir == "u" || this->dir == "d")
					this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(1 * 16, 2 * 16), sf::Vector2i(16, 16)));
				else if (this->dir == "l" || this->dir == "r")
					this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(0 * 16, 2 * 16), sf::Vector2i(16, 16)));
				break;
			}
		}
	}
}

void Tile::handleTail(std::vector<Tile*> *turns)
{
	if (this->part == "tail" && !turns->empty() && this->sprite.getPosition() == turns->at(0)->getTilePos())
	{
		if (turns->at(0)->getDir() == "r")
			this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(9 * 16, 2 * 16), sf::Vector2i(16, 16)));
		else if (turns->at(0)->getDir() == "l")
			this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(7 * 16, 2 * 16), sf::Vector2i(16, 16)));
		else if (turns->at(0)->getDir() == "u")
			this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(6 * 16, 2 * 16), sf::Vector2i(16, 16)));
		else if (turns->at(0)->getDir() == "d")
			this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(8 * 16, 2 * 16), sf::Vector2i(16, 16)));
		
		delete turns->at(0);
		turns->at(0) = NULL;
		turns->erase(turns->begin());
	}
}

void Tile::render(sf::RenderTarget &target)
{
	target.draw(this->sprite);
}

const sf::Vector2f Tile::getTilePos() const
{
	return this->sprite.getPosition();
}

void Tile::setNewSpriteRect(sf::IntRect rect)
{
	this->sprite.setTextureRect(rect);
}