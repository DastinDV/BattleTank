#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_set>

#include "IMovable.h"
#include "BaseUnit.h"
//#include "Map.h"
enum WhoShoot {
	Player,
	AI
};

struct WhoShootClassHash
{
	template <typename T>
	std::size_t operator()(T t) const
	{
		return static_cast<std::size_t>(t);
	}
};

class Bullet : public IMovable, public BaseUnit {
public:
	Bullet();

	virtual void Init() override;
	virtual void Update(const sf::Time& dt, sf::Event& event) override;
	virtual void Render(sf::RenderWindow& window) const override;

	// Реализовать деструктор
	~Bullet();

	virtual void Rotate() override;
	virtual void Move(const sf::Time& dt) override;
	void SetGunner(WhoShoot whoShoot);

private:

	//Map* map1;
	void CheckForHit();
	const std::string PATH = "../Assets/textures/bullet.png";
	const std::unordered_set<int> cantDamageTiles = { 2, 5, 6 };
	const std::unordered_map<WhoShoot, std::unordered_set<int>, WhoShootClassHash> whoShootToIgnoredTiles {
		{ WhoShoot::AI, {0, 9, 98}},
		{ WhoShoot::Player, {0, 9, 99}}
	};

	WhoShoot whoShoot = WhoShoot::Player;
	const int DEAD_FLAG = -1;
};