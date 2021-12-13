#include "Game.h"
#include "C:\Users\User\Downloads\Map.c"
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
	
	////Add basic ambient light to the scene.
	//Ogre::ColourValue ambientColor(1.0f, 1.0f, 1.0f, 1.0f);
	//sceneManager->setAmbientLight(ambientColor);

	sceneManager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	//Initialize the player.
    m_player.init(sceneManager);

	//Add the player camera to be the rendered camera.
    getRenderWindow()->addViewport(m_player.getPlayerCamera());
	
	//Load the base level.
    LevelManager manager;
    manager.init(sceneManager);

	
	
	
}

void Game::update(float dt)
{
	m_player.update(dt);
	//for (size_t i = 0; i < Enemys.size(); i++)
	//{
	//	Ogre::Vector3 playerPos = m_player.getPlayerPosition();
	//	Ogre::Vector3 moveDirection = (playerPos - enemyNodes[i]->getPosition());
	//	moveDirection.normalise();
	//	moveDirection.y = 0.0f;
	//	//enemyNodes[i]->translate(moveDirection * dt * 5.0f);
	//	playerPos.y = 0.0f;
	//	enemyNodes[i]->lookAt(playerPos, Ogre::Node::TransformSpace::TS_WORLD);
	//}
	//if (m_player.getIsShooting())
	//{
	//	m_player.setIsShooting(false);
	//	for (size_t i = 0; i < Enemys.size(); i++)
	//	{
	//		Ogre::Log log("ShootingTest");
	//		Ogre::Ray shootingRay = m_player.getPlayerCamera()->getCameraToViewportRay(0.5f, 0.5f);
	//		Ogre::Vector3 direction = shootingRay.getOrigin() + shootingRay.getDirection() * 1000;
	//		if (CollisionManager::checkLineBox(Enemys[i], shootingRay.getOrigin(), direction))
	//		{
	//			log.logMessage("Removed Enemy");
	//			enemyNodes[i]->removeAllChildren();
	//			sceneManager->destroyEntity(Enemys[i]);
	//			Enemys.erase(Enemys.begin() + i);
	//			enemyNodes.erase(enemyNodes.begin() + i);
	//			i--;
	//			log.logMessage("Hit Enemy");
	//			break;
	//		}
	//	}
	//}
}

bool Game::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	return true;
}
