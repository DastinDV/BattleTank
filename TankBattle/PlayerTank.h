#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class PlayerTank {

public:
	PlayerTank();
	void Update(const sf::Time& dt);
	void Render(sf::RenderWindow& window) const;

private:

	sf::Sprite sprite;
	sf::Texture texture;

	sf::Vector2<int> direction;
	float posX, posY;
	float speed;

	void Init();
	void LoadImage();

	void Rotate();
	void Move(const sf::Time& dt);
};