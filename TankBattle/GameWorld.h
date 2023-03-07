#pragma once
#include <queue>

#include "Map.h"
#include "PlayerTank.h"

class GameWorld {

public:
	GameWorld(Map* pMap);
	void Init();
	void SetMap(Map* pMap);
	Map* GetMap();
	void Update(const sf::Time& dt, sf::Event& event);
	void Render(sf::RenderWindow& window);

private:
	Map* pMap;
	PlayerTank player;
};