#pragma once

#include <windows.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <string>

class Texture
{
private:

public:
	unsigned int textureID;
	std::string type;
	std::string path;
	unsigned int Load(const char * filename);
	void Bind();
};