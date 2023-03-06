#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class PlayerTank {

public:
	PlayerTank();
	void Update(const sf::Time& dt);
	void Render(sf::RenderWindow& window) const;
	void SetPosition(const int posX, const int posY);
	void SetMap(const int* const map);
	int GetWidth() const;

private:

	const int* map;

	sf::Sprite sprite;
	sf::Texture texture;

	sf::Vector2<int> direction;
	float posX, posY;
	float width, height;
	float speed;

	void Init();
	void LoadImage();

	void Rotate();
	void Move(const sf::Time& dt);
};