#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class IMovable {

public:
	void SetMap(Map* map);
	void SetDirection(sf::Vector2<int> direction);
	virtual ~IMovable() {};

protected:
	//const int* map;
	Map* pMap;

	sf::Vector2<int> direction;
	float speed;

	virtual void Rotate() = 0;
	virtual void Move(const sf::Time& dt) = 0;
};
