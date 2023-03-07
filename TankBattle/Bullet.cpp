#include "Bullet.h"

#include <iostream>
#include <algorithm>

Bullet::Bullet() {
	Init();
}

void Bullet::Init() {
	speed = 300.f;
	LoadImage(PATH);
}

void Bullet::Update(const sf::Time & dt, sf::Event& event){
	Move(dt);
}

void Bullet::Render(sf::RenderWindow& window) const {
	window.draw(sprite);
}

void Bullet::Rotate() {
	if (direction == sf::Vector2<int>{0, - 1})
		sprite.setRotation(0);
	else if (direction == sf::Vector2<int>{0, 1})
		sprite.setRotation(180);
	else if (direction == sf::Vector2<int>{1, 0})
		sprite.setRotation(90);
	else if (direction == sf::Vector2<int>{-1, 0})
		sprite.setRotation(270);
}

void Bullet::Move(const sf::Time& dt) {
	sprite.setPosition(posX, posY);
	posX += direction.x * speed * dt.asSeconds();
	posY += direction.y * speed * dt.asSeconds();
	posX = std::clamp((int)posX, 0, 13 * 64);
	posY = std::clamp((int)posY, 0, 13 * 64);
	CheckForHit();
}

void Bullet::CheckForHit() {
	int mapX = posX / 64;
	int mapY = posY / 64;

	if (posX == 0 || posY == 0 || mapX > 12 || mapY > 12) SetDeadFlag();
	else {
		int index = mapY * 13 + mapX;
		int* map = pMap->GetMap();

		if (map[index] != 0 && map[index] != 9) {
			std::cout << map[index] << " " << index << std::endl;
			SetDeadFlag();
			if (!cantDamageTiles.count(map[index])) {
				map[index] = 0;
				pMap->UpdateMapData(index);
				std::cout << "Hit something!" << std::endl;
			}
		}
	}
}

Bullet::~Bullet() {

}