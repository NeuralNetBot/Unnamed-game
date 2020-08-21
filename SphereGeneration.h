#pragma once
#include "Includes.h"
#include "Mesh.h"
#include "Noise.h"

struct VertIndices
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

class SphereGeneration
{
public:
	SphereGeneration() {}
	VertIndices Generate(int subdivisions, double radius);
};

