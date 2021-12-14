#include "EnemiesManager.h"
#include <random>
#include "CollisionManager.h"
void EnemiesManager::init(int numberOfEnemiesToSpawn, int maxTimeBetweenSpawns, int minTimeBetweenSpawns)
{
	m_number_Of_Enemies_To_Spawn = numberOfEnemiesToSpawn;
	m_max_Time_Between_Spawns = maxTimeBetweenSpawns;
	m_min_Time_Between_Spawns = minTimeBetweenSpawns;
	m_time_Until_Next_Spawn = (rand() % m_max_Time_Between_Spawns + m_min_Time_Between_Spawns);
}

void EnemiesManager::update(Ogre::SceneManager* sceneManager, float dt,Vector3& playerPos)
{
	m_spawn_Timer += dt;
	if (m_spawn_Timer >= m_time_Until_Next_Spawn)
	{
		if (m_number_Of_Enemies_To_Spawn > 0)
		{
			m_number_Of_Enemies_To_Spawn--;
			spawnEnemy(sceneManager);
		}
	}
}

void EnemiesManager::damageEnemy(SceneManager* sceneManager, Ray& shootingRay)
{
	Vector3 direction = shootingRay.getOrigin() + shootingRay.getDirection() * 100.0f;
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		if (CollisionManager::checkLineBox(m_enemies[i]->getEnemyMesh(), shootingRay.getOrigin(), direction))
		{
			m_enemies[i]->takeDamage(1);
			if (m_enemies[i]->getHealth() <= 0)
			{
				m_enemies[i]->clear(sceneManager);
				delete m_enemies[i];
				m_enemies.erase(m_enemies.begin() + i);
				i--;
			}
		}
	}
}

void EnemiesManager::spawnEnemy(SceneManager* sceneManager)
{
	m_spawn_Timer = 0.0f;
	m_time_Until_Next_Spawn = (rand() % m_max_Time_Between_Spawns + m_min_Time_Between_Spawns);
	bool inverseXPosition = (rand() % 10 < 5);
	bool inverseYPosition = (rand() % 10 > 5);

	int enemyXPosition = rand() % m_max_Enemy_Spawn_Distance;
	if (enemyXPosition < m_min_Enemy_Spawn_Distance)
	{
		enemyXPosition = m_min_Enemy_Spawn_Distance;
	}
	enemyXPosition *= ((inverseXPosition) ? -1 : 1);

	int enemyYPosition = rand() % m_max_Enemy_Spawn_Distance;
	if (enemyYPosition < m_min_Enemy_Spawn_Distance)
	{
		enemyYPosition = m_min_Enemy_Spawn_Distance;
	}

	enemyYPosition *= ((inverseYPosition) ? -1 : 1);
	Vector3 enemyPos(enemyXPosition, 0.0f, enemyYPosition);

	Ogre::Vector3 enemyScale(1.0f, 1.0f, 1.0f);
	std::string enemyName = "Demon" + std::to_string(m_current_Enemy_Number);
	m_enemies.push_back(EnemyFactories::CreateBaseEnemy(sceneManager, enemyPos, enemyScale, enemyName.c_str()));
	m_current_Enemy_Number++;
}
