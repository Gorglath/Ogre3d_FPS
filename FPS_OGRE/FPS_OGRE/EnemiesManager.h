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
	void init(int numberOfSimpleEnemiesToSpawn,int numberOfFlyingEnemiesToSpawn, int maxTimeBetweenSpawns, int minTimeBetweenSpawns, int difficulty);
	void update(SceneManager* sceneManager, float dt, Vector3 playerPos);
	void damageEnemy(SceneManager* sceneManager, Ray& shootingRay);
	bool checkIfCollidingWithPosition(SceneManager* sceneManager, Vector3 targetPosition);
	void clear(SceneManager* sceneManager);
	inline bool hasEnemyLeftToSpawn() const { return (m_number_Of_Flying_Enemies_To_Spawn > 0 || m_number_Of_Flying_Enemies_To_Spawn > 0); }
private:
	void spawnEnemy(SceneManager* sceneManager,EnemyType type);
	int m_number_Of_Simple_Enemies_To_Spawn{ 10 };
	int m_number_Of_Flying_Enemies_To_Spawn{ 10 };
	int m_max_Time_Between_Spawns{ 10};
	int m_min_Time_Between_Spawns{ 5 };
	int m_time_Until_Next_Spawn{ 0 };
	int m_current_Enemy_Number{ 0 };
	int m_max_Enemy_Spawn_Distance{ 80 };
	int m_min_Enemy_Spawn_Distance{ 50 };
	int m_difficulty{ 0 };
	float m_spawn_Timer{ 0.0f };
	vector<Enemy*> m_enemies{};
};

