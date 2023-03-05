#include "PlayerTank.h"
#include <stdexcept>


PlayerTank::PlayerTank() {
	Init();
}

void PlayerTank::Init() {
	direction = { 0, 1 };
	speed = 200.f;
	LoadImage();
}

void PlayerTank::LoadImage() {
	if (!this->texture.loadFromFile("../Assets/PlayerTank.png")) {
		throw std::runtime_error("Failed to load texture for a player");
	}

	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	posX = sprite.getGlobalBounds().width / 2;
	posY = sprite.getGlobalBounds().height / 2;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		posX += direction.x * speed * dt.asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		posY += direction.y * speed * dt.asSeconds();

	sprite.setPosition(posX, posY);
}

void PlayerTank::Update(const sf::Time& dt) {
	Rotate();
	Move(dt);
}

void PlayerTank::Render(sf::RenderWindow& window) const {
	window.draw(sprite);
}