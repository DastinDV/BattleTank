#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include "IMovable.h"
#include "BaseUnit.h"
//#include "Map.h"

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

private:
	//Map* map1;
	void CheckForHit();
	const std::string PATH = "../Assets/textures/bullet.png";
	const std::unordered_set<int> cantDamageTiles = { 2 , 5, 6};
};