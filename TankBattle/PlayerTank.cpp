#include "PlayerTank.h"
#include "Bullet.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

PlayerTank::PlayerTank() {
	Init();
}

void PlayerTank::Init() {
	direction = { 0, -1 };
	speed = 200.f;
	LoadImage(PATH);
	SetPosition(posX, posY);
}

void PlayerTank::Rotate() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		sprite.setRotation(0);
		direction = { 0 , -1 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sprite.setRotation(270);
		direction = { -1 , 0 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sprite.setRotation(90);
		direction = { 1 , 0 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		sprite.setRotation(180);
		direction = { 0 , 1 };
	}
	
}

bool PlayerTank::MoveUp(const sf::Time& dt) {
	int* map = pMap->GetMap();

	int mapX = posX / width;
	int mapY = posY / height;
	mapY = mapY - 1;

	int index = mapY * 13 + mapX;
	if (!walkableTiles.count(map[index])) {
		posY = std::max(posY + direction.y * speed * dt.asSeconds(),
			mapY * height + height + height / 2);
		return false;
	}
	else {
		posX = (mapX * width) + width / 2;
		posY += direction.y * speed * dt.asSeconds();
	}
	return true;
}

bool PlayerTank::MoveDown(const sf::Time& dt) {
	int* map = pMap->GetMap();

	int mapX = posX / width;
	int mapY = posY / height;
	mapY = mapY + 1;

	int index = mapY * 13 + mapX;
	if (!walkableTiles.count(map[index])) {
		posY = std::min(posY + direction.y * speed * dt.asSeconds(),
			mapY * height - height + height / 2);
		return false;
	}
	else {
		posX = (mapX * width) + width / 2;
		posY += direction.y * speed * dt.asSeconds();
	}
	return true;
}

bool PlayerTank::MoveLeft(const sf::Time& dt) {
	int* map = pMap->GetMap();

	int mapX = posX / width;
	int mapY = posY / height;
	mapX = mapX - 1;

	int index = mapY * 13 + mapX;

	if (!walkableTiles.count(map[index])) {
		posX = std::max(posX + direction.x * speed * dt.asSeconds(),
			mapX * width + width + width / 2);
		return false;
	}
	else {
		posY = (mapY * height) + height / 2;
		posX += direction.x * speed * dt.asSeconds();
	}
	return true;
}

bool PlayerTank::MoveRight(const sf::Time& dt) {
	int* map = pMap->GetMap();

	int mapX = posX / width;
	int mapY = posY / height;
	mapX = mapX + 1;

	int index = mapY * 13 + mapX;

	if (!walkableTiles.count(map[index])) {
		posX = std::min(posX + direction.x * speed * dt.asSeconds(),
			mapX * width - width + width / 2);
		return false;
	}
	else {
		posY = (mapY * height) + height / 2;
		posX += direction.x * speed * dt.asSeconds();
	}
	return true;
}

void PlayerTank::Move(const sf::Time& dt) {

	int* map = pMap->GetMap();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		MoveLeft(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		MoveRight(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		MoveUp(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		MoveDown(dt);
	}

	posX = std::clamp(posX, 0 + width / 2, 13 * width - width / 2);
	posY = std::clamp(posY, 0 + height / 2, 13 * height - height / 2);
	sprite.setPosition(posX, posY);
}

void PlayerTank::Shoot(const sf::Time& dt, sf::Event& event) {
	if (!isShootPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		isShootPressed = true;
		bullets.push_back(CreateBullet());
		std::cout << "Shoot!" << std::endl;
	}

	if (event.type == event.KeyReleased) {
		if (event.key.code == sf::Keyboard::Space)
			isShootPressed = false;
	}

	UpdateBullets(dt, event);
}

Bullet* PlayerTank::CreateBullet() {
	Bullet* bullet = new Bullet();
	bullet->SetDirection(this->direction);
	bullet->Rotate();
	bullet->SetPosition(posX, posY);
	bullet->SetMap(pMap);
	return bullet;
}

void PlayerTank::UpdateBullets(const sf::Time& dt, sf::Event& event) {
	std::list<Bullet*>::iterator i = bullets.begin();
	while (i != bullets.end())
	{
		bool isDead = (*i)->IsDead();
		if (isDead) {
			delete (*i);
			bullets.erase(i++);
		}
		else {
			(*i)->Update(dt, event);
			++i;
		}
	}
}

void PlayerTank::Update(const sf::Time& dt, sf::Event& event) {
	Rotate();
	Move(dt);
	Shoot(dt, event);
}

void PlayerTank::Render(sf::RenderWindow& window) const {
	window.draw(sprite);
	for (auto& bullet : bullets)
		bullet->Render(window);
}