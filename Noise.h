#pragma once
#include "Includes.h"

class Noise
{
private:
	int p[512];

	long long int seed;
	int octaves = 1;
	double frequency = 1;
	double power = 1;

	double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }

	double lerp(double t, double a, double b) { return a + t * (b - a); }

	double grad(int hash, double x, double y, double z)
	{
		int h = hash & 15;
		double u = h < 8 ? x : y,
			v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}

	double Noise3D(glm::vec3 position);
public:
	Noise(long long int seed) { SetSeed(seed); };
	double GetValue(glm::vec3 position);
	void SetSeed(long long int seed);
	void SetOctaves(int octaves);
	void SetFrequency(double frequency);
	void SetPower(double power);
};

