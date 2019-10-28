#pragma once
#include "includes.h"
#include "Components.h"

class Game
{
public:

	void init();
	void update(float dt);

	//TODO: remove these or move them to graphics system!
	GLuint temp_program;
	GLuint temp_texture;
	GLuint temp_vao;
	GLuint temp_tris;

private:

};
