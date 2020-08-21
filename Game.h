#pragma once
#include "Includes.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "SphereGeneration.h"
#include "TextRenderer.h"
#include "Utils.h"
#include "Model.h"

class Game
{
private:
public:
	Game(std::string title, bool fullscreen);
	~Game();
};
