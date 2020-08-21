#pragma once
#include "Includes.h"
#include "soil.h"

namespace Utils
{
	glm::vec3 LatLongToXYZ(glm::vec2 ll);

	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);

}