#include "IMovable.h"

void IMovable::SetMap(Map* map) {
	this->pMap = map;
}

void IMovable::SetSpeed(int speed) {
	this->speed = speed;
}

void IMovable::SetDirection(sf::Vector2<int> direction) {
	this->direction = direction;
}