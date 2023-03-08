#include "AITank.h"
#include "helper.h"
#include "Bullet.h"

#include <random>
#include <fstream>
#include <sstream>
#include <iostream>

AITank::AITank() {
	TankId++;
	std::cout << "TankId" << TankId << std::endl;
}

void AITank::Init() {
	direction = { 0, 1 };
	speed = 250.f;
	ProvideSeed(engine, TankId);
}

void AITank::ChangeRandomDirection() {
	direction = allDirections[GetRandomNumber(engine, 0, allDirections.size(), TankId)];
}

void AITank::Rotate() {
	if (direction == sf::Vector2<int>{0, -1})
		sprite.setRotation(0);
	else if (direction == sf::Vector2<int>{0, 1})
		sprite.setRotation(180);
	else if (direction == sf::Vector2<int>{1, 0})
		sprite.setRotation(90);
	else if (direction == sf::Vector2<int>{-1, 0})
		sprite.setRotation(270);
}

void AITank::Move(const sf::Time& dt) {

	int prevMapX = posX / width;
	int prevMapY = posY / height;

	int prevIndex = prevMapY * 13 + prevMapX;
	if (pMap->GetMap()[prevIndex] == -1) { SetDeadFlag(); pMap->GetMap()[prevIndex] = 0; }
	else pMap->GetMap()[prevIndex] = 98;

	if (direction == sf::Vector2<int>{0, -1})
		canMove = MoveUp(dt);
	else if (direction == sf::Vector2<int>{0, 1})
		canMove = MoveDown(dt);
	else if (direction == sf::Vector2<int>{1, 0})
		canMove = MoveRight(dt);
	else if (direction == sf::Vector2<int>{-1, 0})
		canMove = MoveLeft(dt);

	int mapX = posX / width;
	int mapY = posY / height;

	int index = mapY * 13 + mapX;
	if (index != prevIndex) {
		pMap->GetMap()[prevIndex] = 0;
	}

	if (!canMove) { ChangeRandomDirection(); canMove = true; };
	if (posX < 0 + width / 2 || posX > 13 * width - width / 2) { ChangeRandomDirection(); canMove = true; };
	if (posY < 0 + height / 2 || posY > 13 * height - height / 2) { ChangeRandomDirection(); canMove = true; };

	posX = std::clamp(posX, 0 + width / 2, 13 * width - width / 2);
	posY = std::clamp(posY, 0 + height / 2, 13 * height - height / 2);
	sprite.setPosition(posX, posY);

	passedTime += clock.getElapsedTime().asSeconds();
	if (passedTime >= shootTime) {
		std::cout << "Shoot!" << std::endl;
		passedTime = 0;
		clock.restart();
		bullets.push_back(CreateBullet(WhoShoot::AI));
	}
}


void AITank::Update(const sf::Time& dt, sf::Event& event) {
	Rotate();
	Move(dt);
	UpdateBullets(dt, event);
}

void AITank::Render(sf::RenderWindow& window) const {
	window.draw(sprite);
	RenderBullets(window);
}

void AITank::SetLives(const int lives) {
	this->lives = lives;
}

std::unordered_map<EnemyType, EnemyInf> TankCreator::enemyTypeToInf;

void TankCreator::LoadData() {
	std::ifstream infile("../Assets/enemies.txt");
	std::string line;
	int i = 0;
	std::getline(infile, line);	// skip header;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int id = 0;
		std::string tankType, path, speed, lives;
		iss >> tankType;
		iss >> path;
		iss >> speed;
		iss >> lives;

		sf::Texture* newTileTexture = new sf::Texture();
		if (!newTileTexture->loadFromFile(path)) {
			throw std::runtime_error("Failed to load texture for a tank");
		}

		EnemyInf inf;
		inf.type = static_cast<EnemyType>(atoi(tankType.c_str()));
		inf.speed = atoi(speed.c_str());
		inf.lives = atoi(lives.c_str());
		inf.texture = newTileTexture;

		enemyTypeToInf[inf.type] = inf;
	}
}

std::unordered_map<EnemyType, EnemyInf>& TankCreator::GetEnemyTypeToInf() {
	return enemyTypeToInf;
}

AITank* TankCreator::CreateTank(EnemyType type, int xPos, int yPos) {
	AITank* tank = new AITank();

	auto inf = TankCreator::GetEnemyTypeToInf().at(type);
	tank->SetSpeed(inf.speed);
	tank->SetLives(inf.lives);
	tank->GetSprite().setTexture(*inf.texture);
	tank->GetSprite().setOrigin(tank->GetSpriteWidth() / 2, tank->GetSpriteWidth() / 2);
	tank->SetPosition(xPos + tank->GetSpriteWidth() / 2, yPos + tank->GetSpriteWidth() / 2);
	tank->SetDirection({0, 1});
	tank->SetSpriteBounds(tank->GetSprite().getGlobalBounds().width, 
						  tank->GetSprite().getGlobalBounds().height);
	
	return tank;
}

EnemyType TankCreator::GenRandomTankType(std::mt19937& engine, int id) {
	return static_cast<EnemyType>(GetRandomNumber(engine, 0, 3, id));
}