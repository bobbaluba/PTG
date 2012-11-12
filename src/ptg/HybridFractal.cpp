/**
 * @file HybridFractal.cpp
 * @date 12. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <ptg/HybridFractal.hpp>

#include <cstdlib>
#include <cmath>

namespace ptg {

HybridFractal::HybridFractal(unsigned int seed):
	Continuous2DSignal(seed),
	baseNoise(NULL),
	octaves(7),
	lacunarity(2),
	H(0.25){
	initExponents();
}

HybridFractal::~HybridFractal() {
	initExponents();
}

float HybridFractal::get(float x, float y) {
	float amplitude=1;
	float frequency=1;
	const float offset = 0.7;
	float result= (baseNoise->get(x*frequency, y*frequency)*20 + offset) * exponents[0];
	frequency = lacunarity;
	float weight = result;
	for(unsigned int i = 1; i < octaves; i++){
		if(weight>1)weight=1; //prevent divergence
		float signal = (baseNoise->get(x*frequency,y*frequency)*20 + offset) * exponents[i];
		result += weight * signal;
		weight *= signal; // update the monotonically decreasing weight

		frequency *= lacunarity;
	}
	return result*amplitude-offset/2.0;
}

void ptg::HybridFractal::onReSeed(unsigned int seed) {
	baseNoise->seed(seed);
}

void HybridFractal::initExponents() {
	exponents.clear();
	exponents.reserve(octaves);
	float frequency = 1.0;
	for(unsigned int i=1; i<octaves; i++){
		// compute spectral weight for each frequency */
		exponents.push_back(pow( frequency, -H*i ));
		frequency *= lacunarity;
	}
}

}//namespace ptg

