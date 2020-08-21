#pragma once
#include "Includes.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"
#include "Utils.h"


class Model
{
public:
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	
	std::string texture_diffuse = "";
	std::string texture_normal = "";
	std::string texture_emission = "";

	int texture_diffuse_id;
	int texture_normal_id;
	int texture_emission_id;

	bool load_materials = true;

	Model()
	{

	}

	Model(std::string const& path, bool load_materials = true) : load_materials(load_materials)
	{
		loadModel(path);
	}

	void LoadMaterials(std::string texture_diffuse, std::string texture_normal, std::string texture_emission)
	{
		this->texture_diffuse = texture_diffuse;
		this->texture_normal = texture_normal;
		this->texture_emission = texture_emission;
		//assumes only 1 mesh
		meshes.at(0).textures.clear();
		if (texture_diffuse != "")
		{
			texture_diffuse_id = Utils::TextureFromFile(texture_diffuse.c_str(), this->directory, false);
			meshes.at(0).textures.push_back(Texture(texture_diffuse_id, "texture_diffuse", texture_diffuse.c_str()));
		}
		if (texture_normal != "")
		{
			texture_normal_id = Utils::TextureFromFile(texture_normal.c_str(), this->directory, false);
			meshes.at(0).textures.push_back(Texture(texture_normal_id, "texture_normal", texture_normal.c_str()));
		}
		
		if (texture_emission != "")
		{
			texture_emission_id = Utils::TextureFromFile(texture_emission.c_str(), this->directory, false);
			meshes.at(0).textures.push_back(Texture(texture_emission_id, "texture_emission", texture_emission.c_str()));
		}
		
	}

	void Draw(Shader shader)
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);
	}

private:
	void loadModel(std::string const& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene);
	}

	void processNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			std::cout << i << std::endl;
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}

	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

