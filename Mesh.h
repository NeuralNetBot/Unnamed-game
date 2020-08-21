#pragma once
#include "Includes.h"
#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	bool operator==(Vertex e) const { return e.Position == Position; };
};

struct Texture {
	Texture() {}
	Texture(unsigned int id, std::string type, std::string path) : id(id), type(type), path(path) { }
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int VAO;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		setupMesh();
	}

	void UpdateMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void UpdateMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void Draw(Shader shader);

private:
	unsigned int VBO, EBO;

	void setupMesh();
};