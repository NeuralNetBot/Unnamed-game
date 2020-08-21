#include "SphereGeneration.h"
#include <random>
#include <time.h>

VertIndices SphereGeneration::Generate(int subdivisions, double radius)
{
	std::vector<Vertex> mesh;

	const glm::vec3 origins[6] =
	{
		glm::vec3(-1.0, -1.0, -1.0),
		glm::vec3(1.0, -1.0, -1.0),
		glm::vec3(1.0, -1.0, 1.0),
		glm::vec3(-1.0, -1.0, 1.0),
		glm::vec3(-1.0, 1.0, -1.0),
		glm::vec3(-1.0, -1.0, 1.0)
	};
	const glm::vec3 rights[6] =
	{
		glm::vec3(2.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, 2.0),
		glm::vec3(-2.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, -2.0),
		glm::vec3(2.0, 0.0, 0.0),
		glm::vec3(2.0, 0.0, 0.0)
	};
	const glm::vec3 ups[6] =
	{
		glm::vec3(0.0, 2.0, 0.0),
		glm::vec3(0.0, 2.0, 0.0),
		glm::vec3(0.0, 2.0, 0.0),
		glm::vec3(0.0, 2.0, 0.0),
		glm::vec3(0.0, 0.0, 2.0),
		glm::vec3(0.0, 0.0, -2.0)
	};

	const double step = 1.0 / double(subdivisions);
	const glm::vec3 step3(step, step, step);
	
	Noise* pnoise = new Noise(23413);
	pnoise->SetFrequency(3);
	pnoise->SetOctaves(3);
	for (int face = 0; face < 6; face++)
	{
		const glm::vec3 origin = origins[face];
		const glm::vec3 right = rights[face];
		const glm::vec3 up = ups[face];
		for (uint32_t j = 0; j < subdivisions + 1; ++j)
		{
			const glm::vec3 j3(j, j, j);
			for (uint32_t i = 0; i < subdivisions + 1; ++i)
			{
				const glm::vec3 i3(i, i, i);
				const glm::vec3 p = origin + step3 * (i3 * right + j3 * up);
				const glm::vec3 p2 = p * p;
				glm::normalize(p);

				glm::vec3 n
				(
					radius * p.x * std::sqrt(1.0 - 0.5 * (p2.y + p2.z) + p2.y * p2.z / 3.0),
					radius * p.y * std::sqrt(1.0 - 0.5 * (p2.z + p2.x) + p2.z * p2.x / 3.0),
					radius * p.z * std::sqrt(1.0 - 0.5 * (p2.x + p2.y) + p2.x * p2.y / 3.0)
				);
				
				double noise = pnoise->GetValue(n);
				std::cout << noise << std::endl;
				n.x *= noise;
				n.y *= noise;
				n.z *= noise;
				
				double PI = 3.14159265358979323846264338327950288;
				Vertex vert;
				vert.Position = n;
				vert.Normal = glm::normalize(vert.Position);
				vert.TexCoords = glm::vec2((atan2(vert.Normal.x, vert.Normal.z)/(2 * PI) + 0.5), vert.Normal.y * 0.5 + 0.5);
				/*
				glm::vec2 temptexcoords = glm::vec2(1 - (double)i / subdivisions, (double)j / subdivisions);
				
				switch (face)
				{
					case 0:
						vert.TexCoords = (temptexcoords * glm::vec2(.25, .25)) + glm::vec2(.25, .5);
						break;
					case 1:
						vert.TexCoords = (temptexcoords * glm::vec2(.25, .25)) + glm::vec2(0, .5);
						break;
					case 2:
						vert.TexCoords = (temptexcoords * glm::vec2(.25, .25)) + glm::vec2(.75, .5);
						break;
					case 3:
						vert.TexCoords = (temptexcoords * glm::vec2(.25, .25)) + glm::vec2(.5, .5);
						break;
					case 4:
						vert.TexCoords = (temptexcoords * glm::vec2(.25, .25)) + glm::vec2(.25, .75);
						break;
					case 5:
						vert.TexCoords = (temptexcoords * glm::vec2(.25, .25)) + glm::vec2(.25, .25);
						break;
				}
				*/
				mesh.emplace_back(vert);
			}
		}
	}


	std::cout << mesh.size() << std::endl;
	std::vector<unsigned int> mesh_indices;

	const uint32_t k = subdivisions + 1;
	for (uint32_t face = 0; face < 6; ++face)
	{
		for (uint32_t j = 0; j < subdivisions; ++j)
		{
			const bool bottom = j < (subdivisions / 2);
			for (uint32_t i = 0; i < subdivisions; ++i)
			{
				const bool left = i < (subdivisions / 2);
				const uint32_t a0 = (face * k + j) * k + i;
				const uint32_t b0 = (face * k + j) * k + i + 1;
				const uint32_t c0 = (face * k + j + 1) * k + i;
				const uint32_t d0 = (face * k + j + 1) * k + i + 1;
				uint32_t a = a0;
				uint32_t b = c0;
				uint32_t c = d0;
				uint32_t d = b0;

				if (bottom ^ left)
				{
					mesh_indices.emplace_back(a);
					mesh_indices.emplace_back(b);
					mesh_indices.emplace_back(d);
					mesh_indices.emplace_back(b);
					mesh_indices.emplace_back(c);
					mesh_indices.emplace_back(d);
				}
				else
				{
					mesh_indices.emplace_back(a);
					mesh_indices.emplace_back(b);
					mesh_indices.emplace_back(c);
					mesh_indices.emplace_back(a);
					mesh_indices.emplace_back(c);
					mesh_indices.emplace_back(d);
				}
			}
		}
	}

	VertIndices e;
	e.vertices = mesh;
	e.indices = mesh_indices;

	return e;
}