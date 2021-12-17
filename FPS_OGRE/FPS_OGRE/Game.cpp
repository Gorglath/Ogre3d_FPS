#include "Game.h"
#include "EnemyFactories.hpp"
#include <filesystem>
Game::Game() : OgreBites::ApplicationContext("Test")
{
}

void Game::setup(void)
{
	//Get the path to the current folder.
	std::filesystem::path app_path = std::filesystem::current_path();
	std::string app_path_string = app_path.string();

	//Add the assets path to the resource manager.
	ResourceGroupManager* rgm = ResourceGroupManager::getSingletonPtr();
	rgm->addResourceLocation(app_path_string + "\\Assets\\models", "FileSystem");
	rgm->addResourceLocation(app_path_string + "\\Assets\\materials\\textures", "FileSystem");
	rgm->addResourceLocation(app_path_string + "\\Assets\\materials\\scripts", "FileSystem");
	rgm->addResourceLocation(app_path_string + "\\Assets\\Main", "FileSystem");
	rgm->addResourceLocation(app_path_string + "\\Assets\\RTShaderLib\\GLSL", "FileSystem");
	rgm->addResourceLocation(app_path_string + "\\Assets\\particles", "FileSystem");

	//Load all the game sounds.
	m_sound_Manager.loadSounds();

	//Set up the game rendering options.
	Ogre::RenderSystem* renderSys = getRoot()->getRenderSystem();

	renderSys->setConfigOption("Full Screen", "No");
	renderSys->setConfigOption("Video Mode", "800 x 600 @ 32 - bit colour");

	//Setup the ogre application.
	OgreBites::ApplicationContext::setup();

	//Setup the input listeners.
	setUpInputListeners();

	//Initialze the game.
	initializeGame();
}

void Game::update(float dt)
{
	//Check if the escape key was press.
	if (m_player.getIsQuiting())
	{
		//Quit the game.
		getRoot()->queueEndRendering();
	}

	//Update the player.
	m_player.update(dt);
	Ogre::Vector3 playerPos = m_player.getPlayerPosition();

	//Update the level elements.
	m_level_Manager.update(m_scene_Manager, dt,playerPos,m_sound_Manager);

	//Check if the player is shooting.
	if (m_player.getIsShooting())
	{
		//Play shooting sound and set shooting to false.
		m_sound_Manager.playSound("Gun_Shot", 1, true);
		m_player.setIsShooting(false);

		//Get the shooting direction from the middle of the screen.
		Ogre::Ray shootingRay = m_player.getPlayerCamera()->getCameraToViewportRay(0.5f, 0.5f);

		//Check if any enemy was hit.
		m_level_Manager.checkIfHitEnemy(m_scene_Manager, shootingRay,m_sound_Manager);
	}

	//Check if any enemy collided with the player.
	if (m_level_Manager.checkIfPlayerGotHit(m_scene_Manager, playerPos))
	{
		m_sound_Manager.playSound("Player_Hit", 1, true);
		//Take one damage and check if the player is dead.
		m_player.takeDamage(1);
		if (m_player.getIsDead())
		{
			//Restart the current level.
			restart();
		}
	}

	//Check if all the enemies were killed.
	if (!m_level_Manager.getHasEnemiesLeft())
	{
		//Load the next level.
		m_current_Level++;
		restart();
	}
}

/// <summary>
/// Clears all the gameplay elements and reinitialize them.
/// </summary>
void Game::restart()
{
	//Detach the scene manager from the shader generator.
	Ogre::RTShader::ShaderGenerator* shaderGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->removeSceneManager(m_scene_Manager);

	//Clear all viewports.
	getRenderWindow()->removeAllViewports();

	//Clear the level.
	m_level_Manager.clear(m_scene_Manager);

	//Clear the player.
	m_player.clear(m_scene_Manager);
	
	//Clear the scene manager.
	getRoot()->destroySceneManager(m_scene_Manager);
	
	//Initialize the game again.
	initializeGame();
}

void Game::initializeGame()
{
	//Get the application root and create a new scene manager.
	Ogre::Root* root = getRoot();
	m_scene_Manager = root->createSceneManager();

	//Initialize shader generator.
	Ogre::RTShader::ShaderGenerator* shaderGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->addSceneManager(m_scene_Manager);

	//Add basic ambient light to the scene.
	m_scene_Manager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

	//Initialize the player.
	m_player.init(m_scene_Manager);

	//Add the player camera to be the rendered camera.
	getRenderWindow()->addViewport(m_player.getPlayerCamera());

	//Load the level (Includes enemies).
	m_level_Manager.init(m_scene_Manager, m_current_Level);

	//Play the current round sounds and start the music.
	std::string roundSoundName = "Round_" + std::to_string(m_current_Level);
	m_sound_Manager.loopSound("Music", 3, true);
	m_sound_Manager.playSound(roundSoundName.c_str(), 4, true);
}

/// <summary>
/// Sets up all the game input listeners.
/// </summary>
void Game::setUpInputListeners()
{
	//Get the input manager as input listener and add it to listen to input.
	OgreBites::InputListener* input = &m_input_Manager;
	addInputListener(input);

	//Set the input for the player class.
	KeyboardInput* playerKeyboardInput = &m_player;
	m_input_Manager.addKeyboardInputListener(playerKeyboardInput);

	MouseMovementInput* playerMouseMovementInput = &m_player;
	m_input_Manager.addMouseMovementListener(playerMouseMovementInput);

	MouseButtonInput* playerMouseButtonInput = &m_player;
	m_input_Manager.addMouseButtonListener(playerMouseButtonInput);
}
