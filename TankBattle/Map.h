#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "PlayerTank.h"

class Map {
public:
	Map();
	~Map();
	static void ParseCommon();
	void Update(const sf::Time& dt);
	void Render(sf::RenderWindow& window) const;

private:

	int* map;
	const int mapWidth = 13;
	const int mapHeight = 13;
	const int tileWidth = 64;
	const int tileHeight = 64;
	PlayerTank player;

	static std::unordered_map<int, std::string> idToTextureName;
	static std::unordered_map<int, sf::Texture*> idToTexture;
	std::vector<sf::Sprite> tiles;

	void ParseMapData();
};