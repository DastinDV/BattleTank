#include "BaseUnit.h"

void BaseUnit::Init() {

}

void BaseUnit::SetSpriteBounds(float width, float height) {
	this->width = width;
	this->height = height;
}

void BaseUnit::SetPosition(const int posX, const int posY) {
	sprite.setPosition(posX, posY);
	this->posX = posX;
	this->posY = posY;
};

void BaseUnit::SetDeadFlag() {
	this->isAlive = false;
}

bool BaseUnit::IsDead() {
	return !this->isAlive;
}

sf::Sprite& BaseUnit::GetSprite() {
	return this->sprite;
}

int BaseUnit::GetSpriteWidth() const {
	return width;
}

void BaseUnit::LoadImage(const std::string path) {
	if (!this->texture.loadFromFile(path)) {
		throw std::runtime_error("Failed to load texture for a player");
	}

	this->sprite.setTexture(this->texture);
	this->width = sprite.getGlobalBounds().width;
	this->height = sprite.getGlobalBounds().height;
	this->sprite.setOrigin(width / 2, height / 2);
}