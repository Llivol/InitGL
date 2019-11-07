#include "Game.h"
#include "extern.h"
#include "Shader.h"

void Game::init() {

	//******** OLD CODE **********//
    	
	//init graphics system
	graphics_system_.init();

	//load a shader
	graphics_system_.loadShader("phong", "data/shaders/phong.vert", "data/shaders/phong.frag");
	graphics_system_.temp_texture = graphics_system_.loadTexture("data/assets/test.tga");

	int ent_plane = ECS.createEntity("plane");
	Mesh& pmc = ECS.createComponentForEntity<Mesh>(ent_plane);
	graphics_system_.createPlaneGeometry(pmc.vao, pmc.num_tris);	

	//******** NEW CODE **********//

	//TODO in GraphicsSystem.h and GraphicsSystem.cpp
	// - fill properties of Material and Geometry structs
	// - create storage vectors for Materials and Geometries
	// - create function to create/access/update materials and geometries
	// - optional: modify createPlaneGeometry so it creates a geometry directly in storage vector
	// - change render function so it uses geometry and material of component
	
	//TODO in Component.h
	// - modify Mesh Component to store
	//		- index of geometry (in graphics system storage array)
	//		- index of material (in graphics system storage array)

	//TODO here in Game.cpp
	// - Create plane geometry and store in graphics system
	// - create material and store it in graphics system
	// - Create Entity for plane (as code above)
	// - Create Mesh Component for plane (modified from code above) to set material and geometry correctly
	
	//TODO: Advanced
	// - add a function to GraphicsSystem to parse an OBJ file and store it's geometry

}

//Entry point for game update code
void Game::update(float dt) {

	graphics_system_.update(dt);

}

