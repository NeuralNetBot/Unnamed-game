#include "Utils.h"

namespace Utils
{
	glm::vec3 LatLongToXYZ(glm::vec2 ll)
	{
		const double DEG_TO_RAD = 3.14159265358979323846264338327950288 / 180;
		double r = cos(DEG_TO_RAD * ll.x);
		return glm::vec3(r * cos(DEG_TO_RAD * ll.y), sin(DEG_TO_RAD * ll.x), r * sin(DEG_TO_RAD * ll.y));
	}

	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
	{
		std::string filename = std::string(path);
		filename = directory + '/' + filename;

		unsigned int texID = 0;
		int width;
		int height;
		unsigned char* data;

		texID = SOIL_load_OGL_texture
		(
			filename.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			0
		);
		std::cout << texID << std::endl;
		if (texID == 0)
		{
			std::cout << "SOIL loading error: " << SOIL_last_result() << " FileName: " << filename.c_str() << std::endl;
			return 0;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		return texID;
	}
}