/**
 * @file PerlinNoise.cpp
 * @date 22. okt. 2012
 * @author Johan Klokkhammer Helsing
 *
 * Implementation is partly inspired by this tutorial:
 * http://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/
 *
 * And, of course, Ken Perlin's own presentation:
 * http://www.noisemachine.com/talk1/
 */

#include <ptg/PerlinNoise.hpp>

#include <helsing/hmath.hpp>

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
	std::uniform_real_distribution<float> distribution(0, 2*helsing::pi());
	for(unsigned int i=0; i<SAMPLES; ++i){
		//choose a random direction
		float angle = distribution(randomEngine);

		//calculate x and y components of the unit vector
		gradients[i]=helsing::Vec2(cos(angle), sin(angle));
	}
}

PerlinNoise::~PerlinNoise() {
}

float PerlinNoise::get(float x, float y) {
	using helsing::Vec2;
	//determine the grid points
	int gridX=static_cast<int>(x);
	int gridY=static_cast<int>(y);

	const float dx = x-gridX;
	const float dy = y-gridY;

	const Vec2 gAA = gradients[hash(gridX,gridY)];
	const Vec2 gAB = gradients[hash(gridX,gridY+1)];
	const Vec2 gBA = gradients[hash(gridX+1,gridY)];
	const Vec2 gBB = gradients[hash(gridX+1,gridY+1)];

	const float left = helsing::smootherStep(1-dx);
	const float right = helsing::smootherStep(dx);
	const float top = helsing::smootherStep(dy);
	const float bottom = helsing::smootherStep(1-dy);

	float val = 0; // accumulator for the point value
	val += left  * bottom * (gAA*Vec2(dx,dy));
	val += left  * top    * (gAB*Vec2(dx,dy-1));
	val += right * bottom * (gBA*Vec2(dx-1,dy));
	val += right * top    * (gBB*Vec2(dx-1,dy-1));
	return val;
}

void PerlinNoise::onReSeed(unsigned int seed) {
	init();
}

}//namespace ptg
