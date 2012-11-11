/**
 * @file ValueNoise.cpp
 * @date 11. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <ptg/ValueNoise.hpp>

#include <helsing/hmath.hpp>

#include <random>

namespace ptg {

ValueNoise::ValueNoise(unsigned int seed) :
		Continuous2DSignal(seed) {
	init();
}

void ValueNoise::init() {
	//Initialize a random engine with the seed
	std::default_random_engine randomEngine(getSeed());

	std::uniform_real_distribution<float> distribution(-0.5, 0.5);
	for(unsigned int i=0; i<SAMPLES*SAMPLES; ++i){
		samples[i] = distribution(randomEngine);
	}
}

ValueNoise::~ValueNoise() {
}

float ValueNoise::get(float x, float y) {
	//determine the grid points
	int gridX=static_cast<int>(x);
	int gridY=static_cast<int>(y);

	const float dx = x - static_cast<int>(x),
				dy = y - static_cast<int>(y);

	using helsing::smootherStep;
	const float left   = smootherStep(1-dx), // contribution from points on the left
				right  = smootherStep(dx),
				bottom = smootherStep(1-dy),
				top    = smootherStep(dy);

	float val = 0; // accumulator for the point value
	val+= left  * bottom * getSample(gridX  , gridY); //bl
	val+= right * bottom * getSample(gridX+1, gridY); //br
	val+= right * top    * getSample(gridX+1, gridY+1); //tr
	val+= left  * top    * getSample(gridX  , gridY+1); //tl

	return val;
}

void ValueNoise::onReSeed(unsigned int seed) {
	init();
}

}//namespace ptg
