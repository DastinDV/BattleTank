#pragma once
#include <SFML/Graphics.hpp>

class BaseUnit {

public:

	virtual void Init();
	virtual void LoadImage(const std::string path);
	int GetSpriteWidth() const;
	void SetPosition(const int posX, const int posY);

protected:

	float posX, posY;
	float width, height;
	sf::Sprite sprite;
	sf::Texture texture;
};