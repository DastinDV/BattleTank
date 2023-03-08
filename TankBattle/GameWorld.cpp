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

	TankCreator::LoadData();
	AITank* tank = TankCreator::CreateTank(TankCreator::GenRandomTankType(engine, AITank::TankId), 0, 0);
	tank->SetMap(pMap);
	enemies.push_back(tank);

	AITank* tank1 = TankCreator::CreateTank(TankCreator::GenRandomTankType(engine, AITank::TankId), 64 * 6, 0);
	tank1->SetMap(pMap);
	enemies.push_back(tank1);

	AITank* tank2 = TankCreator::CreateTank(TankCreator::GenRandomTankType(engine, AITank::TankId), 64 * 12, 0);
	tank2->SetMap(pMap);
	enemies.push_back(tank2);

	TankCreator::LoadData();
	AITank* tank3 = TankCreator::CreateTank(TankCreator::GenRandomTankType(engine, AITank::TankId), 64 * 6, 64 * 4);
	tank3->SetMap(pMap);
	enemies.push_back(tank3);
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

	std::list<AITank*>::iterator i = enemies.begin();
	while (i != enemies.end())
	{
		bool isDead = (*i)->IsDead();
		if (isDead) {
			delete (*i);
			enemies.erase(i++);
		}
		else {
			(*i)->Update(dt, event);
			++i;
		}
	}

	/*for (auto enemy : enemies) {
		enemy->Update(dt, event);
	}*/
}

void GameWorld::Render(sf::RenderWindow& window) {
	pMap->Render(window);
	player.Render(window);
	for (auto enemy : enemies) {
		enemy->Render(window);
	}
}

GameWorld::~GameWorld() {
	delete pMap;
}