#pragma once
#include <fstream>
#include <filesystem>
#include "json.hpp"
using json = nlohmann::json;
class LevelParser
{
public:
	LevelParser() = default;
	~LevelParser() = default;
	bool tryParseLevel(int number)
	{
		std::filesystem::path levelPath = std::filesystem::current_path();
		levelPath.append("Assets\\levels\\" + std::to_string(number) + ".json");
		std::ifstream i(levelPath);

		if (i) 
		{
			json levelJson;
			i >> levelJson;

			m_number_Of_Simple_Enemies = levelJson["simpleEnemies"];
			m_number_Of_Flying_Enemies = levelJson["flyingEnemies"];
			m_max_Spawn_Time = levelJson["maxSpawnTime"];
			m_min_Spawn_Time = levelJson["minSpawnTime"];
			m_difficulty = levelJson["difficulty"];

		}
		else
		{
			return false;
		}
	}

	inline int getNumberOfSimpleEnemies() { return m_number_Of_Simple_Enemies; }
	inline int getNumberOfFlyingEnemies() { return m_number_Of_Flying_Enemies; }
	inline int getMaxSpawnTime() { return m_max_Spawn_Time; }
	inline int getMinSpawnTime() { return m_min_Spawn_Time; }
	inline int getDifficulty() { return m_difficulty; }
private:
	int m_number_Of_Simple_Enemies{ 10 };
	int m_number_Of_Flying_Enemies{ 10 };
	int m_max_Spawn_Time{ 5 };
	int m_min_Spawn_Time{ 2 };
	int m_difficulty{ 0 };
};