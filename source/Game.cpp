#include "Game.h"
#include "extern.h"
#include "Shader.h"
#include "Texture.h"

void Game::init() {

	//******** INITIALISATION CODE **********//
    
	//set 'background' colour of framebuffer
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	int pepe = ECS.createComponent<Transform>();
	int popo = ECS.createComponent<Transform>();
	int bob = 0;
}

//Entry point for game update code
void Game::update(float dt) {



}

