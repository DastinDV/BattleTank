#include <iostream>
#include <algorithm>

#include "Bullet.h"

Bullet::Bullet() {
	Init();
}

void Bullet::Init() {
	speed = 300.f;
	LoadImage(PATH);
	isAlive = true;
}

void Bullet::SetGunner(WhoShoot whoShoot) {
	this->whoShoot = whoShoot;
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
		//std::cout << "WhoShoot " << whoShoot << std::endl;

		if ((whoShoot == WhoShoot::AI && !whoShootToIgnoredTiles.at(WhoShoot::AI).count(map[index])) ||
			(whoShoot == WhoShoot::Player && !whoShootToIgnoredTiles.at(WhoShoot::Player).count(map[index]))) {
			//std::cout << map[index] << " " << index << std::endl;
			SetDeadFlag();
			if (!cantDamageTiles.count(map[index])) {
				if (whoShoot == WhoShoot::Player && map[index] == 98) {	// Tank was killed. Update map.
					map[index] = DEAD_FLAG;
				} else map[index] = 0;
				pMap->UpdateMapData(index, 0);
				std::cout << "Hit something!" << std::endl;
			}
		}
	}
}

Bullet::~Bullet() {

}
