#pragma once
#include <vector>
#include <random>

#include "Map.h"
#include "PlayerTank.h"
#include "AITank.h"

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
	std::vector<AITank*> enemies;
	std::mt19937 engine;
};