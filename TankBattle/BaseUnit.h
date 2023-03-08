#pragma once
#include <SFML/Graphics.hpp>
//#include "Map.h"

class BaseUnit {

public:
	int GetSpriteWidth() const;
	sf::Sprite& GetSprite();
	void SetPosition(const int posX, const int posY);
	void SetSpriteBounds(float width, float height);
	void SetDeadFlag();
	bool IsDead();

	virtual void Init();
	virtual void LoadImage(const std::string path);
	virtual void Update(const sf::Time& dt, sf::Event& event) = 0;
	virtual void Render(sf::RenderWindow& window) const = 0;

	virtual ~BaseUnit() {};
protected:

	//Map* pMap;
	float posX, posY;
	float prevX, prevY;
	float width, height;
	sf::Sprite sprite;
	sf::Texture texture;
	bool isAlive = true;
};