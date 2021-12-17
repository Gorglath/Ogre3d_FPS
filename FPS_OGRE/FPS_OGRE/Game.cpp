#include "Game.h"
#include "EnemyFactories.hpp"
Game::Game() : OgreBites::ApplicationContext("Test")
{
}

void Game::setup(void)
{
	m_sound_Manager.loadSounds();

	Ogre::RenderSystem* renderSys = getRoot()->getRenderSystem();

	renderSys->setConfigOption("Full Screen", "No");
	renderSys->setConfigOption("Video Mode", "800 x 600 @ 32 - bit colour");

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

	m_level_Manager.update(m_scene_Manager, dt,playerPos,m_sound_Manager);

	if (m_player.getIsShooting())
	{
		m_sound_Manager.playSound("Gun_Shot", 1, true);
		m_player.setIsShooting(false);
		Ogre::Ray shootingRay = m_player.getPlayerCamera()->getCameraToViewportRay(0.5f, 0.5f);
		m_level_Manager.checkIfHitEnemy(m_scene_Manager, shootingRay,m_sound_Manager);
	}

	if (m_level_Manager.checkIfPlayerGotHit(m_scene_Manager, playerPos))
	{
		m_sound_Manager.playSound("Player_Hit", 1, true);
		m_playerHealth--;
		if (m_playerHealth <= 0)
		{
			m_playerHealth = 3;
			restart();
		}
	}

	if (!m_level_Manager.getHasEnemyLeftToSpawn())
	{
		m_current_Level++;
		restart();
	}
}


void Game::restart()
{
	Ogre::RTShader::ShaderGenerator* shaderGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->removeSceneManager(m_scene_Manager);
	getRenderWindow()->removeAllViewports();

	m_level_Manager.clear(m_scene_Manager);
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
	m_level_Manager.init(m_scene_Manager, m_current_Level);

	std::string roundSoundName = "Round_" + std::to_string(m_current_Level);
	m_sound_Manager.loopSound("Music", 3, true);
	m_sound_Manager.playSound(roundSoundName.c_str(), 4, true);
}
