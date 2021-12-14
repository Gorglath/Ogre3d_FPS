#include "EnemiesManager.h"
#include <random>
#include "CollisionManager.h"
void EnemiesManager::init(int numberOfSimpleEnemiesToSpawn, int numberOfFlyingEnemiesToSpawn, int maxTimeBetweenSpawns, int minTimeBetweenSpawns)
{
	m_number_Of_Simple_Enemies_To_Spawn = numberOfSimpleEnemiesToSpawn;
	m_number_Of_Flying_Enemies_To_Spawn = numberOfFlyingEnemiesToSpawn;
	m_max_Time_Between_Spawns = maxTimeBetweenSpawns;
	m_min_Time_Between_Spawns = minTimeBetweenSpawns;
	m_time_Until_Next_Spawn = (rand() % m_max_Time_Between_Spawns + m_min_Time_Between_Spawns);
}

void EnemiesManager::update(Ogre::SceneManager* sceneManager, float dt,Vector3& playerPos)
{
	m_spawn_Timer += dt;
	if (m_spawn_Timer >= m_time_Until_Next_Spawn)
	{
		int randomType = rand() % 2;
		if (randomType == 1)
		{
			if (m_number_Of_Simple_Enemies_To_Spawn > 0)
			{
				m_number_Of_Simple_Enemies_To_Spawn--;
				spawnEnemy(sceneManager,EnemyType::SIMPLE);
			}
			else
			{
				if (m_number_Of_Flying_Enemies_To_Spawn > 0)
				{
					m_number_Of_Flying_Enemies_To_Spawn--;
					spawnEnemy(sceneManager, EnemyType::FLYING);
				}
			}
		}
		else
		{
			if (m_number_Of_Flying_Enemies_To_Spawn > 0)
			{
				m_number_Of_Flying_Enemies_To_Spawn--;
				spawnEnemy(sceneManager, EnemyType::FLYING);
			}
			else
			{
				if (m_number_Of_Simple_Enemies_To_Spawn > 0)
				{
					m_number_Of_Simple_Enemies_To_Spawn--;
					spawnEnemy(sceneManager, EnemyType::SIMPLE);
				}
			}
		}
	}

	for (auto& enemy : m_enemies)
	{
		enemy->update(playerPos,dt);
	}
}

void EnemiesManager::damageEnemy(SceneManager* sceneManager, Ray& shootingRay)
{
	int closestEnemyIndex = -1;
	bool hitFirstEnemy = false;
	Vector3 direction = shootingRay.getOrigin() + shootingRay.getDirection() * 100.0f;
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		if (CollisionManager::checkLineBox(m_enemies[i]->getEnemyMesh(), shootingRay.getOrigin(), direction))
		{
			if (!hitFirstEnemy)
			{
				hitFirstEnemy = true;
				closestEnemyIndex = i;
			}
			else
			{
				float closestDistance = m_enemies[closestEnemyIndex]->getEnemyPosition().distance(shootingRay.getOrigin());
				float currentEnemyDistance = m_enemies[i]->getEnemyPosition().distance(shootingRay.getOrigin());
				if (closestDistance > currentEnemyDistance)
				{
					closestEnemyIndex = i;
				}
			}
		}
	}
	
	if (hitFirstEnemy)
	{
		m_enemies[closestEnemyIndex]->takeDamage(1);
		if (m_enemies[closestEnemyIndex]->getHealth() <= 0)
		{
			m_enemies[closestEnemyIndex]->clear(sceneManager);
			delete m_enemies[closestEnemyIndex];
			m_enemies.erase(m_enemies.begin() + closestEnemyIndex);
		}
	}
}

void EnemiesManager::spawnEnemy(SceneManager* sceneManager,EnemyType type)
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
	Vector3 enemyPos(enemyXPosition, ((type == EnemyType::FLYING)? 50.0f:0.0f), enemyYPosition);

	Ogre::Vector3 enemyScale(1.0f, 1.0f, 1.0f);
	std::string enemyName = "Demon" + std::to_string(m_current_Enemy_Number);
	Enemy* enemy = nullptr;
	switch (type)
	{
	case EnemyType::FLYING:
		enemy = EnemyFactories::CreateFlyingEnemy(sceneManager, enemyPos, enemyScale, enemyName.c_str());
		enemy->init(3, 10);
		break;
	case EnemyType::SIMPLE:
		enemy = EnemyFactories::CreateSimpleEnemy(sceneManager, enemyPos, enemyScale, enemyName.c_str());
		enemy->init(5, 20);
		break;
	default:
		enemy = EnemyFactories::CreateBaseEnemy(sceneManager, enemyPos, enemyScale, enemyName.c_str());
		enemy->init(3, 5);
		break;
	}

	
	m_enemies.push_back(enemy);
	m_current_Enemy_Number++;
}
