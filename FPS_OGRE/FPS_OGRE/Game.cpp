#include "Game.h"
#include "OgreLog.h"
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

	//Get the application starting point and create a new scene manager in that point.
	Ogre::Root* root = getRoot();
	Ogre::SceneManager* sceneManager = root->createSceneManager();

	//Initialize shader generator.
	Ogre::RTShader::ShaderGenerator* shaderGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->addSceneManager(sceneManager);
	
	//Add basic ambient light to the scene.
	Ogre::ColourValue ambientColor(1.0f, 1.0f, 1.0f, 1.0f);
	sceneManager->setAmbientLight(ambientColor);

	//Initialize the player.
    m_player.init(sceneManager);

	//Add the player camera to be the rendered camera.
    getRenderWindow()->addViewport(m_player.getPlayerCamera());
	
	//Load the base level.
    LevelManager manager;
    manager.init(sceneManager);

	Ogre::SceneNode* barrelNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	barrelNode->setPosition(Ogre::Vector3(5.0f, 3.0f, 5.0f));
	barrelNode->scale(0.5f, 0.5f, 0.5f);
	barrel = sceneManager->createEntity("Barrel", "Barrel.mesh");
	barrelNode->attachObject(barrel);
}

void Game::update(float dt)
{
	m_player.update(dt);
	if (m_player.getIsShooting())
	{
		Ogre::Log log("ShootingTest");
		Ogre::Ray shootingRay = m_player.getPlayerCamera()->getCameraToViewportRay(0.5f, 0.5f);
		Ogre::Vector3 direction = shootingRay.getOrigin() + shootingRay.getDirection() * 10.0f;
		if (CollisionManager::checkLineBox(barrel, shootingRay.getOrigin(), direction))
		{
			log.logMessage("Hit Barrel");
		}
		else
		{
			log.logMessage("Missed Barrel");
		}
	}
}

bool Game::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	return true;
}
