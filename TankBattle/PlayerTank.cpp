#include "PlayerTank.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

PlayerTank::PlayerTank() {
	Init();
}

void PlayerTank::Init() {
	direction = { 0, 1 };
	speed = 200.f;
	LoadImage();
}

void PlayerTank::LoadImage() {
	if (!this->texture.loadFromFile("../Assets/textures/PlayerTank.png")) {
		throw std::runtime_error("Failed to load texture for a player");
	}

	this->sprite.setTexture(this->texture);
	this->width = sprite.getGlobalBounds().width;
	this->height = sprite.getGlobalBounds().height;
	this->sprite.setOrigin(width / 2, height / 2);
	this->posX = width / 2;
	this->posY = height / 2;
	this->sprite.setPosition(posX, posY);

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
			posX = mapX * width + width + width / 2;
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
			posX = mapX * width - width + width / 2;
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
			posY = mapY * height + height + height / 2;
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
			posY = mapY * height - height + height / 2;
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

void PlayerTank::Update(const sf::Time& dt) {
	Rotate();
	Move(dt);
}

void PlayerTank::Render(sf::RenderWindow& window) const {
	window.draw(sprite);
}

int PlayerTank::GetWidth() const {
	return this->width;
}

void PlayerTank::SetPosition(const int posX, const int posY) {
	sprite.setPosition(posX, posY);
	this->posX = posX;
	this->posY = posY;
}

void PlayerTank::SetMap(const int* const map) {
	this->map = map;
}