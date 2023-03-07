#pragma once
#include <SFML/Graphics.hpp>

class IMovable {

public:
	void SetMap(const int* const map);
	virtual ~IMovable() {};

protected:
	const int* map;

	sf::Vector2<int> direction;
	float speed;

	virtual void Rotate() = 0;
	virtual void Move(const sf::Time& dt) = 0;
};