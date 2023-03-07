#pragma once
#include <SFML/Graphics.hpp>
#include "IMovable.h"
#include "BaseUnit.h"

class Bullet : public IMovable, public BaseUnit {
public:
	Bullet();
	virtual void Init() override;

private:

	virtual void Rotate() override;
	virtual void Move(const sf::Time& dt) override;
};