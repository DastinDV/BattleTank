#include "GameWorld.h"

GameWorld::GameWorld(Map* pMap) {
	this->pMap = pMap;
	Init();
}

void GameWorld::Init() {
	player.SetPosition(
		pMap->GetPlayerPosition().x + player.GetSpriteWidth() / 2,
		pMap->GetPlayerPosition().y);
	player.SetMap(pMap);
}

void GameWorld::SetMap(Map* pMap) {
	this->pMap = pMap;
}

Map* GameWorld::GetMap() {
	return pMap;
}

void GameWorld::Update(const sf::Time& dt, sf::Event& event) {
	pMap->Update(dt, event);
	player.Update(dt, event);
}

void GameWorld::Render(sf::RenderWindow& window) {
	pMap->Render(window);
	player.Render(window);
}