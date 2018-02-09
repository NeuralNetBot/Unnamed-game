#pragma once
#include <Windows.h>
#include "Shader.h"
#include <GL/GL.h>
#include <GL/GLU.h>
#include <glm\glm.hpp>
#include <string>
#include <vector>
#include "Texture.h"
using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

class Mesh {
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;
	
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		setupMesh();
	}

	void Draw(Shader shader);

private:
	unsigned int VBO, EBO;

	void setupMesh();
};