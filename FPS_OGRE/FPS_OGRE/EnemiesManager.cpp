#include "EnemiesManager.h"
#include <random>
#include "CollisionManager.h"
/// <summary>
/// Initialize the enemy manager.
/// </summary>
/// <param name="numberOfSimpleEnemiesToSpawn"></param>
/// <param name="numberOfFlyingEnemiesToSpawn"></param>
/// <param name="maxTimeBetweenSpawns"></param>
/// <param name="minTimeBetweenSpawns"></param>
/// <param name="difficulty"></param>
void EnemiesManager::init(int numberOfSimpleEnemiesToSpawn, int numberOfFlyingEnemiesToSpawn
	, int maxTimeBetweenSpawns, int minTimeBetweenSpawns,int difficulty)
{
	m_number_Of_Simple_Enemies_To_Spawn = numberOfSimpleEnemiesToSpawn;
	m_number_Of_Flying_Enemies_To_Spawn = numberOfFlyingEnemiesToSpawn;
	m_max_Time_Between_Spawns = maxTimeBetweenSpawns;
	m_min_Time_Between_Spawns = minTimeBetweenSpawns;
	m_time_Until_Next_Spawn = (rand() % m_max_Time_Between_Spawns + m_min_Time_Between_Spawns);
	m_difficulty = difficulty;
}

void EnemiesManager::update(Ogre::SceneManager* sceneManager, float dt,Vector3 playerPos, SoundManager& soundManager)
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
				soundManager.playSound("Enemy_Spawn", 1, true);
				spawnEnemy(sceneManager,EnemyType::SIMPLE);
			}
			else
			{
				if (m_number_Of_Flying_Enemies_To_Spawn > 0)
				{
					m_number_Of_Flying_Enemies_To_Spawn--;
					soundManager.playSound("Enemy_Spawn", 1, true);
					spawnEnemy(sceneManager, EnemyType::FLYING);
				}
			}
		}
		else
		{
			if (m_number_Of_Flying_Enemies_To_Spawn > 0)
			{
				m_number_Of_Flying_Enemies_To_Spawn--;
				soundManager.playSound("Enemy_Spawn", 1, true);
				spawnEnemy(sceneManager, EnemyType::FLYING);
			}
			else
			{
				if (m_number_Of_Simple_Enemies_To_Spawn > 0)
				{
					m_number_Of_Simple_Enemies_To_Spawn--;
					soundManager.playSound("Enemy_Spawn", 1, true);
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
/// <summary>
/// Damager the first enemy hit by the ray.
/// </summary>
/// <param name="sceneManager"></param>
/// <param name="shootingRay"></param>
/// <param name="soundManager"></param>
void EnemiesManager::damageEnemy(SceneManager* sceneManager, Ray& shootingRay, SoundManager& soundManager)
{
	int closestEnemyIndex = -1;
	bool hitFirstEnemy = false;
	//Get the ray direction.
	Vector3 direction = shootingRay.getOrigin() + shootingRay.getDirection() * 100.0f;
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		if (CollisionManager::checkLineBox(m_enemies[i]->getEnemyMesh(), shootingRay.getOrigin(), direction))
		{
			//Get the first enemy hit as the closest enemy to the ray origin.
			if (!hitFirstEnemy)
			{
				hitFirstEnemy = true;
				closestEnemyIndex = i;
			}
			else
			{
				//Check which enemy is closer to the ray origin.
				float closestDistance = m_enemies[closestEnemyIndex]->getEnemyPosition().distance(shootingRay.getOrigin());
				float currentEnemyDistance = m_enemies[i]->getEnemyPosition().distance(shootingRay.getOrigin());
				if (closestDistance > currentEnemyDistance)
				{
					closestEnemyIndex = i;
				}
			}
		}
	}
	
	//Check if any enemy was hit.
	if (hitFirstEnemy)
	{
		soundManager.playSound("Enemy_Hit", 2, true);

		m_enemies[closestEnemyIndex]->takeDamage(1);
		if (m_enemies[closestEnemyIndex]->getHealth() <= 0)
		{
			soundManager.playSound("Enemy_Death", 2, true);
			//Remove the enemy from the game.
			clearEnemy(0, sceneManager);
		}
	}
}

/// <summary>
/// Check if any enemy is colliding with a give 3d position.
/// </summary>
/// <param name="sceneManager"></param>
/// <param name="targetPosition"></param>
/// <returns></returns>
bool EnemiesManager::checkIfCollidingWithPosition(SceneManager* sceneManager, Vector3 targetPosition)
{
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		//Check if the enemy is close enough to considered a collision target.
		if (m_enemies[i]->getEnemyPosition().distance(targetPosition) < 10.0f)
		{
			if (CollisionManager::checkCollisionWithPoint(m_enemies[i]->getEnemyMesh(), targetPosition))
			{
				clearEnemy(0, sceneManager);
				break;
			}
		}
	}
	return false;
}

/// <summary>
/// Remove all enemies from the game.
/// </summary>
/// <param name="sceneManager"></param>
void EnemiesManager::clear(SceneManager* sceneManager)
{
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		clearEnemy(0, sceneManager);
	}
}

/// <summary>
/// Remove an enemy at a given index from the game.
/// </summary>
/// <param name="index"></param>
/// <param name="sceneManager"></param>
void EnemiesManager::clearEnemy(int index, SceneManager* sceneManager)
{
	m_enemies[index]->clear(sceneManager);
	delete m_enemies[index];
	m_enemies.erase(m_enemies.begin() + index);
}

/// <summary>
/// Spawns a certain enemy type at a random location.
/// </summary>
/// <param name="sceneManager"></param>
/// <param name="type"></param>
void EnemiesManager::spawnEnemy(SceneManager* sceneManager,EnemyType type)
{
	m_spawn_Timer = 0.0f;
	m_time_Until_Next_Spawn = (rand() % m_max_Time_Between_Spawns + m_min_Time_Between_Spawns);

	//Check if the x or y spawn position should be inversed.
	bool inverseXPosition = (rand() % 10 < 5);
	bool inverseYPosition = (rand() % 10 > 5);

	//Get the x spawn position and limit it between max and min.
	int enemyXPosition = rand() % m_max_Enemy_Spawn_Distance;
	if (enemyXPosition < m_min_Enemy_Spawn_Distance)
	{
		enemyXPosition = m_min_Enemy_Spawn_Distance;
	}
	enemyXPosition *= ((inverseXPosition) ? -1 : 1);

	//Get the y spawn position and limit it between max and min.
	int enemyYPosition = rand() % m_max_Enemy_Spawn_Distance;
	if (enemyYPosition < m_min_Enemy_Spawn_Distance)
	{
		enemyYPosition = m_min_Enemy_Spawn_Distance;
	}
	enemyYPosition *= ((inverseYPosition) ? -1 : 1);
	
	//Initilize enemy parameters.
	Vector3 enemyPos(enemyXPosition, ((type == EnemyType::FLYING)? 50.0f:0.0f), enemyYPosition);
	Ogre::Vector3 enemyScale(1.0f, 1.0f, 1.0f);
	Enemy* enemy = nullptr;

	//Set the current enemy name (must be different for each enemy).
	std::string enemyName = "Demon" + std::to_string(m_current_Enemy_Number);
	
	float difficultyIncrementation = (m_difficulty * 2);
	//Spawn and initialize the given enemy type.
	switch (type)
	{
	case EnemyType::FLYING:
		enemy = EnemyFactories::CreateFlyingEnemy(sceneManager, enemyPos, enemyScale, enemyName.c_str());
		enemy->init(3, 10 + difficultyIncrementation);
		break;
	case EnemyType::SIMPLE:
		enemy = EnemyFactories::CreateSimpleEnemy(sceneManager, enemyPos, enemyScale, enemyName.c_str());
		enemy->init(5 + difficultyIncrementation, 20);
		break;
	default:
		enemy = EnemyFactories::CreateBaseEnemy(sceneManager, enemyPos, enemyScale, enemyName.c_str());
		enemy->init(3, 5);
		break;
	}

	//Add the enemy to the enemies vector.
	m_enemies.push_back(enemy);
	m_current_Enemy_Number++;
}
