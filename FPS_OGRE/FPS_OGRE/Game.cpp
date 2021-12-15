#include "Game.h"
#include "EnemyFactories.hpp"
Game::Game() : OgreBites::ApplicationContext("Test")
{
}

void Game::setup(void)
{
	//Setup the ogre application.
	OgreBites::ApplicationContext::setup();

	OgreBites::InputListener* input = &m_input_Manager;
	//Add this object to receive input events.
	addInputListener(input);
	KeyboardInput* playerKeyboardInput = &m_player;
	m_input_Manager.addKeyboardInputListener(playerKeyboardInput);

	MouseMovementInput* playerMouseMovementInput = &m_player;
	m_input_Manager.addMouseMovementListener(playerMouseMovementInput);

	MouseButtonInput* playerMouseButtonInput = &m_player;
	m_input_Manager.addMouseButtonListener(playerMouseButtonInput);

	
	initializeGame();
}

void Game::update(float dt)
{
	m_player.update(dt);
	Ogre::Vector3 playerPos = m_player.getPlayerPosition();

	m_levelManager.update(m_scene_Manager, dt,playerPos);

	if (m_player.getIsShooting())
	{
		m_player.setIsShooting(false);
		Ogre::Ray shootingRay = m_player.getPlayerCamera()->getCameraToViewportRay(0.5f, 0.5f);
		m_levelManager.checkIfHitEnemy(m_scene_Manager, shootingRay);
	}

	if (m_levelManager.checkIfPlayerGotHit(m_scene_Manager, playerPos))
	{
		m_playerHealth--;
		if (m_playerHealth <= 0 || !m_levelManager.getHasEnemyLeftToSpawn())
		{
			m_playerHealth = 3;
			restart();
		}
	}

	if (!m_levelManager.getHasEnemyLeftToSpawn())
	{
		m_currentLevel++;
		restart();
	}
}


void Game::restart()
{
	Ogre::RTShader::ShaderGenerator* shaderGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->removeSceneManager(m_scene_Manager);
	getRenderWindow()->removeAllViewports();

	m_levelManager.clear(m_scene_Manager);
	m_player.clear(m_scene_Manager);
	
	getRoot()->destroySceneManager(m_scene_Manager);
	
	initializeGame();
}

void Game::initializeGame()
{
	//Get the application starting point and create a new scene manager in that point.
	Ogre::Root* root = getRoot();
	m_scene_Manager = root->createSceneManager();

	//Initialize shader generator.
	Ogre::RTShader::ShaderGenerator* shaderGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->addSceneManager(m_scene_Manager);

	////Add basic ambient light to the scene.

	m_scene_Manager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

	//Initialize the player.
	m_player.init(m_scene_Manager);
	//Add the player camera to be the rendered camera.
	getRenderWindow()->addViewport(m_player.getPlayerCamera());

	//Load the base level.
	m_levelManager.init(m_scene_Manager, m_currentLevel);
}
