#pragma once
#include <unordered_map>
#include <random>

#include "PlayerTank.h"

enum EnemyType {
	Enemy,
	FastEnemy,
	StrongEnemy
};

struct EnemyInf {
	EnemyType type;
	sf::Texture* texture;
	int speed;
	int lives;
};

class AITank : public PlayerTank {
public:
	AITank();
	virtual void Update(const sf::Time& dt, sf::Event& event) override;
	virtual void Render(sf::RenderWindow& window) const override;

	void SetLives(const int lives);

	static inline int TankId = 0;
private:
	void Init() override;
	virtual void Rotate() override;
	virtual void Move(const sf::Time& dt) override;

	void ChangeRandomDirection();

	int lives;
	bool canMove = true;
	static std::unordered_map<EnemyType, EnemyInf> enemyTypeToInf;

	std::mt19937 engine;
};

class TankCreator {
public:
	static AITank* CreateTank(EnemyType type, int xPos, int yPos);
	static EnemyType GenRandomTankType(std::mt19937& engine, int id);
	static std::unordered_map<EnemyType, EnemyInf>& GetEnemyTypeToInf();
	static void LoadData();

private:
	static std::unordered_map<EnemyType, EnemyInf> enemyTypeToInf;
};