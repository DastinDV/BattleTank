#include "Map.h"
#include <fstream>
#include <sstream>
#include <iostream>

Map::Map() {
	ParseMapData();
	player.SetMap(this->map);
}

std::unordered_map<int, std::string> Map::idToTextureName;
std::unordered_map<int, sf::Texture*> Map::idToTexture;

void Map::ParseCommon() {
	std::ifstream infile("../Assets/maps/common.txt");
	std::string line;
	int i = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int id = 0;
		std::string textureName, buf;
		iss >> id;
		iss >> buf;
		iss >> textureName;
		idToTextureName[id] = textureName;

		sf::Texture* newTileTexture = new sf::Texture();
		if (!newTileTexture->loadFromFile("../Assets/textures/" + textureName)) {
			throw std::runtime_error("Failed to load texture for a map");
		}
		idToTexture[id] = newTileTexture;
	}
}

void Map::ParseMapData() {

	map = new int[mapHeight * mapWidth];

	std::ifstream infile("../Assets/maps/map1.txt");

	std::string line;
	int i = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		std::string nextTileID;
		while (getline(iss, nextTileID, ' ')) {
			map[i++] = atoi(nextTileID.c_str());
		}
	}

	int xTilePos = 0;
	int yTilePos = 0;
	for (int i = 0, k = 0; i < mapHeight * mapWidth; i++, k++) {
		sf::Sprite tileSprite;

		if (map[i] == 9)
			player.SetPosition(xTilePos + (player.GetWidth() / 2), yTilePos);
		if (idToTexture.count(map[i])) {
			tileSprite.setTexture(*idToTexture[map[i]]);
			tileSprite.setPosition(xTilePos, yTilePos);
			xTilePos += tileWidth;
			if (k == 12) { xTilePos = 0; yTilePos += tileHeight; k = -1; }
			tiles.push_back(tileSprite);
		}
	}

	for (int i = 0, k = 0; i < mapHeight * mapWidth; i++, k++) {
		std::cout << map[i] << " ";
		if (k == 12) { std::cout << std::endl; k = -1; }
	}
}


void Map::Update(const sf::Time& dt) {
	player.Update(dt);
}

void Map::Render(sf::RenderWindow& window) const {
	for (auto& item : tiles)
		window.draw(item);
	player.Render(window);
}

Map::~Map() {
	delete[] map;
}