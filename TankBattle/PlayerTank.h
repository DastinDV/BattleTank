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
	~PlayerTank();

protected:
	void Init() override;

	virtual void Rotate() override;
	virtual void Move(const sf::Time& dt) override;
	void Shoot(const sf::Time& dt, sf::Event& event);
	Bullet* CreateBullet(WhoShoot whoShoot);

	bool MoveUp(const sf::Time& dt);
	bool MoveDown(const sf::Time& dt);
	bool MoveLeft(const sf::Time& dt);
	bool MoveRight(const sf::Time& dt);
	void UpdateBullets(const sf::Time& dt, sf::Event& event);
	void RenderBullets(sf::RenderWindow& window) const;

	std::list<Bullet*> bullets;
private:

	bool isShootPressed = false;
	const std::string PATH = "../Assets/textures/PlayerTank.png";
	const std::unordered_set<int> walkableTiles = { 0, 9 };
};