#include "IMovable.h"

void IMovable::SetMap(const int* const map) {
	this->map = map;
}

void IMovable::SetDirection(sf::Vector2<int> direction) {
	this->direction = direction;
}
