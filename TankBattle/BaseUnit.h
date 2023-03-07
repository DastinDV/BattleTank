#pragma once
#include <SFML/Graphics.hpp>

class BaseUnit {

public:
	int GetSpriteWidth() const;
	void SetPosition(const int posX, const int posY);
	void SetDeadFlag();
	bool IsDead();

	virtual void Init();
	virtual void LoadImage(const std::string path);
	virtual void Update(const sf::Time& dt, sf::Event& event) = 0;
	virtual void Render(sf::RenderWindow& window) const = 0;

	virtual ~BaseUnit() {};
protected:

	float posX, posY;
	float width, height;
	sf::Sprite sprite;
	sf::Texture texture;
	bool isAlive = true;
};