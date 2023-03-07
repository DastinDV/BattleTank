#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "IMovable.h"
#include "BaseUnit.h"

class PlayerTank : public IMovable, public BaseUnit {

public:
	PlayerTank();
	void Update(const sf::Time& dt);
	void Render(sf::RenderWindow& window) const;

private:

	void Init() override;

	virtual void Rotate() override;
	virtual void Move(const sf::Time& dt) override;
	const std::string PATH = "../Assets/textures/PlayerTank.png";
};