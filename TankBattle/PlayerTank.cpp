#include "PlayerTank.h"
#include "Bullet.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

PlayerTank::PlayerTank() {
	Init();
}

void PlayerTank::Init() {
	direction = { 0, 1 };
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

void PlayerTank::Move(const sf::Time& dt) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		int mapX = posX / width;
		int mapY = posY / height;
		mapX = mapX - 1;

		int index = mapY * 13 + mapX;

		if (map[index] != 0 && map[index] != 9) {
			posX = std::max(posX + direction.x * speed * dt.asSeconds(), 
				mapX * width + width + width / 2);
		}
		else {
			posY = (mapY * height) + height / 2;
			posX += direction.x * speed * dt.asSeconds();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		int mapX = posX / width;
		int mapY = posY / height;
		mapX = mapX + 1;

		int index = mapY * 13 + mapX;

		if (map[index] != 0 && map[index] != 9) {
			posX = std::min(posX + direction.x * speed * dt.asSeconds(), 
				mapX * width - width + width / 2);
		}
		else {
			posY = (mapY * height) + height / 2;
			posX += direction.x * speed * dt.asSeconds();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		int mapX = posX / width;
		int mapY = posY / height;
		mapY = mapY - 1;
		
		int index = mapY * 13 + mapX;
		if (map[index] != 0 && map[index] != 9) {
			posY = std::max(posY + direction.y * speed * dt.asSeconds(),
				mapY * height + height + height / 2);
		}
		else {
			posX = (mapX * width) + width / 2;
			posY += direction.y * speed * dt.asSeconds();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		int mapX = posX / width;
		int mapY = posY / height;
		mapY = mapY + 1;

		int index = mapY * 13 + mapX;
		if (map[index] != 0 && map[index] != 9) {
			posY = std::min(posY + direction.y * speed * dt.asSeconds(),
				mapY * height - height + height / 2);
		}
		else {
			posX = (mapX * width) + width / 2;
			posY += direction.y * speed * dt.asSeconds();
		}
	}

	posX = std::clamp(posX, 0 + width / 2, 13 * width - width / 2);
	posY = std::clamp(posY, 0 + height / 2, 13 * height - height / 2);
	sprite.setPosition(posX, posY);
}

void PlayerTank::Shoot(const sf::Time& dt, sf::Event& event) {
	if (!isShootPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		isShootPressed = true;
		Bullet* bullet = new Bullet();
		bullet->SetDirection(this->direction);
		bullet->Rotate();
		bullet->SetPosition(posX, posY);
		bullet->SetMap(map);
		bullets.push_back(bullet);
		std::cout << "Shoot!" << std::endl;
	}

	if (event.type == event.KeyReleased) {
		if (event.key.code == sf::Keyboard::Space)
			isShootPressed = false;
	}

	//std::cout << "Bullet count " << bullets.size() << std::endl;
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