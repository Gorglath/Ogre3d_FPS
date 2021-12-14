#pragma once
#include "Ogre.h"
#include "EnemyFactories.hpp"
#include "Enemy.h"
#include <vector>

using namespace Ogre;
using std::vector;
class EnemiesManager
{
public:
	EnemiesManager() = default;
	~EnemiesManager() = default;
	void init(int numberOfEnemiesToSpawn, int maxTimeBetweenSpawns, int minTimeBetweenSpawns);
	void update(SceneManager* sceneManager, float dt);
private:
	void spawnEnemy(SceneManager* sceneManager);
	int m_number_Of_Enemies_To_Spawn{ 10 };
	int m_max_Time_Between_Spawns{ 10};
	int m_min_Time_Between_Spawns{ 5 };
	int m_time_Until_Next_Spawn{ 0 };
	int m_current_Enemy_Number{ 0 };
	int m_max_Enemy_Spawn_Distance{ 80 };
	int m_min_Enemy_Spawn_Distance{ 50 };
	float m_spawn_Timer{ 0.0f };
	vector<Enemy*> m_enemies{};
};

