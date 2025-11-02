#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Tile
{
private:
	sf::Sprite sprite;
	std::string part;
	std::string dir;
public:
	Tile(sf::Texture &texture, sf::IntRect rect, std::string part, sf::Vector2f pos, std::string dir);
	~Tile();

	const std::string &getPart() const;
	const std::string &getDir() const;
	void changeDir(std::string newDir);
	void moveTile();
	void handleHead(std::string newDir, std::vector<Tile*> *turns, sf::Texture &texture);
	void handleBody(std::vector<Tile*> &turns);
	void handleTail(std::vector<Tile*> *turns);
	void render(sf::RenderTarget &target);
	const sf::Vector2f getTilePos() const;
	void setNewSpriteRect(sf::IntRect rect);
};


#endif