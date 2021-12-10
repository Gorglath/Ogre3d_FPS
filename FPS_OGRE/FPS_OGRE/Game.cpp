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
	sceneManager = root->createSceneManager();

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

	enemyNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	enemyNode->setPosition(Ogre::Vector3(5.0f, 0.0f, 5.0f));
	Enemy = sceneManager->createEntity("Barrel", "Demon.mesh");
	Enemy->setMaterialName("Penguin");
	enemyNode->attachObject(Enemy);
}

void Game::update(float dt)
{
	m_player.update(dt);
	if (isEnemyAlive) 
	{
		Ogre::Vector3 playerPos = m_player.getPlayerPosition();
		Ogre::Vector3 moveDirection = (playerPos - enemyNode->getPosition());
		moveDirection.normalise();
		moveDirection.y = 0.0f;
		enemyNode->translate(moveDirection * dt * 5.0f);
		playerPos.y = 0.0f;
		enemyNode->lookAt(playerPos, Ogre::Node::TransformSpace::TS_WORLD);

		if (m_player.getIsShooting())
		{
			m_player.setIsShooting(false);
			Ogre::Log log("ShootingTest");
			Ogre::Ray shootingRay = m_player.getPlayerCamera()->getCameraToViewportRay(0.5f, 0.5f);
			Ogre::Vector3 direction = shootingRay.getOrigin() + shootingRay.getDirection() * 100.0f;
			if (CollisionManager::checkLineBox(Enemy, shootingRay.getOrigin(), direction))
			{
				enemyLives--;
				if (enemyLives <= 0)
				{
					log.logMessage("Removed Enemy");
					isEnemyAlive = false;
					enemyNode->removeAllChildren();
					sceneManager->destroyEntity(Enemy);
				}
				log.logMessage("Hit Enemy");
			}
			else
			{
				log.logMessage("Missed Enemy");
			}
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
