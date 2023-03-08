#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>

#include "IMovable.h"
#include "BaseUnit.h"
#include "Bullet.h"

class PlayerTank : public IMovable, public BaseUnit {

public:
	PlayerTank();
	virtual void Update(const sf::Time& dt, sf::Event& event) override;
	virtual void Render(sf::RenderWindow& window) const override;

protected:
	void Init() override;

	virtual void Rotate() override;
	virtual void Move(const sf::Time& dt) override;
	void Shoot(const sf::Time& dt, sf::Event& event);
	Bullet* CreateBullet();

	bool MoveUp(const sf::Time& dt);
	bool MoveDown(const sf::Time& dt);
	bool MoveLeft(const sf::Time& dt);
	bool MoveRight(const sf::Time& dt);

private:
	void UpdateBullets(const sf::Time& dt, sf::Event& event);

	std::list<Bullet*> bullets;
	bool isShootPressed = false;
	const std::string PATH = "../Assets/textures/PlayerTank.png";
	const std::unordered_set<int> walkableTiles = { 0, 9 };
};