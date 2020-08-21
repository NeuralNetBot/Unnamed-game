#include "Noise.h"


double Noise::Noise3D(glm::vec3 position)
{
    int X = (int)floor(position.x) & 255, Y = (int)floor(position.y) & 255, Z = (int)floor(position.z) & 255;
    position.x -= floor(position.x);
    position.y -= floor(position.y);
    position.z -= floor(position.z);

    double u = fade(position.x),
        v = fade(position.y),
        w = fade(position.z);
    int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z,
        B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

    return lerp(w, lerp(v, lerp(u, grad(p[AA], position.x, position.y, position.z),
			grad(p[BA], position.x - 1, position.y, position.z)),
			lerp(u, grad(p[AB], position.x, position.y - 1, position.z),
            grad(p[BB], position.x - 1, position.y - 1, position.z))),
			lerp(v, lerp(u, grad(p[AA + 1], position.x, position.y, position.z - 1),
            grad(p[BA + 1], position.x - 1, position.y, position.z - 1)),
            lerp(u, grad(p[AB + 1], position.x, position.y - 1, position.z - 1),
            grad(p[BB + 1], position.x - 1, position.y - 1, position.z - 1))));
}

double Noise::GetValue(glm::vec3 position)
{
	position *= frequency;

	double value = 0;

	double multiplier = 1;

	for (int i = 0; i < octaves; i++)
	{
		double octavefrequency = i+1;
		value += Noise3D(glm::vec3(position.x * octavefrequency, position.x * octavefrequency, position.x * octavefrequency));
		multiplier /= 2;
		i *= 2;
	}

	value = pow(value, power);

	return value / 2 + 0.5;
}

void Noise::SetSeed(long long int seed)
{
	this->seed = seed;

	for (size_t i = 0; i < 256; ++i)
	{
		p[i] = static_cast<std::uint8_t>(i);
	}

	std::shuffle(std::begin(p), std::begin(p) + 256, std::default_random_engine(seed));

	for (size_t i = 0; i < 256; ++i)
	{
		p[256 + i] = p[i];
	}
}

void Noise::SetOctaves(int octaves)
{
	this->octaves = octaves;
}

void Noise::SetFrequency(double frequency)
{
	this->frequency = frequency;
}

void Noise::SetPower(double power)
{
	this->power = power;
}