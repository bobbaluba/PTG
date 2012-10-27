/*
 * PerlinNoise.cpp
 *
 *  Created on: 22. okt. 2012
 *      Author: johan
 *
 */

#include "PerlinNoise.h"

#include <helsing/hmath.h>

#include <numeric>
#include <algorithm>
#include <functional>
#include <random>

namespace ptg {

PerlinNoise::PerlinNoise(unsigned int seed) :
		Continuous2DSignal(seed) {
	init();
}

void PerlinNoise::init() {
	//First we are going to set up the hash function

	//Fill permutations with indices from 0 to SAMPLES
	std::iota(permutations.begin(), permutations.end(), 0);

	//Initialize a random engine with seed
	std::default_random_engine randomEngine(getSeed());

	//Shuffle using the above random engine
	std::shuffle(permutations.begin(), permutations.end(), randomEngine);

	//set up the random gradients of unit length
	for(unsigned int i=0; i<SAMPLES; ++i){
		//choose a random direction
		std::uniform_real_distribution<float> distribution(0, helsing::pi());
		float angle = distribution(randomEngine);

		//calculate x and y components of the unit vector
		gradients[i]=helsing::Vec2(cos(angle), sin(angle));
	}
}

PerlinNoise::~PerlinNoise() {
}

float PerlinNoise::get(float x, float y) {
	//determine the grid points
	int gridX=static_cast<int>(x);
	int gridY=static_cast<int>(y);

	helsing::Vec2 point(x,y);

	float val = 0; // accumulator for the point value
	val += gridPointContribution(gridX, gridY, point);
	val += gridPointContribution(gridX, gridY + 1, point);
	val += gridPointContribution(gridX + 1, gridY, point);
	val += gridPointContribution(gridX + 1, gridY + 1, point);

	return val;
}

unsigned int PerlinNoise::hash(int x, int y) {
	//perlins original implementation used a performance optimization trick where
	//he exploited byte overflow as an automatic modulus function. This requires samples=256
	//another trick is to use a bit mask, although this has a less strict requirement, it still
	//requires samples to be a power of two. I used modulo here for modifiability and readability purposes
	return permutations[(y+permutations[x%SAMPLES])%SAMPLES];
}

float PerlinNoise::gridPointContribution(int x, int y, const helsing::Vec2& position) {
	//get the gradient for the current gridpoint
	const helsing::Vec2& gradient = gradients[hash(x,y)];

	const helsing::Vec2 gridPoint(x,y);

	//compute the contribution from the gridpoint
	const float beforeDropoff = (position - gridPoint) * gradient; //dot product of gradient and offset from gridPoint

	//compute the dropoff
	const float dropoffX = helsing::smoothStep(1-fabs(position.x - gridPoint.x));
	const float dropoffY = helsing::smoothStep(1-fabs(position.y - gridPoint.y));
	const float dropoff = dropoffX*dropoffY;

	return beforeDropoff*dropoff;
}

void PerlinNoise::onReSeed(unsigned int seed) {
	init();
}

}//namespace ptg
