/*
 * PerlinNoise.cpp
 *
 *  Created on: 22. okt. 2012
 *      Author: johan
 */

#include "PerlinNoise.h"

#include <numeric>
#include <algorithm>
#include <functional>

PerlinNoise::PerlinNoise(unsigned int seed) :
		Continuous2DSignal(seed) {
	//Fill permutations with indices from 0 to SAMPLES
	std::iota(permutations.begin(), permutations.end(), 0);

	//Initialize a random engine with seed
	std::default_random_engine randomEngine(seed);

	//Shuffle using the above random engine
	std::shuffle(permutations.begin(), permutations.end(), randomEngine);


}

PerlinNoise::~PerlinNoise() {
}

float PerlinNoise::get(float x, float y) {
	return 0;
}

const helsing::Vec2& PerlinNoise::hash(int x, int y) {
}

float PerlinNoise::gridPointContribution(int x, int y,
		const helsing::Vec2& position) {
}

float PerlinNoise::gridPointContribution(int x, int y,
		const helsing::Vec2& position) {
}

float PerlinNoise::gridPointContribution(int x, int y,
		const helsing::Vec2& position) {
}
