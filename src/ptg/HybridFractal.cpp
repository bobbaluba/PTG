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
	offset(0.7),
	H(0.25){
	initExponents();
}

HybridFractal::~HybridFractal() {
	initExponents();
}

float HybridFractal::get(float x, float y) {
	float frequency=1;
	float value= (baseNoise->get(x*frequency, y*frequency)*2 + offset) * exponents[0];
 	frequency = lacunarity;
	float weight = value;
	for(unsigned int i = 1; i < octaves; i++){
		if(weight>1)weight=1; //prevent divergence
		float signal = (baseNoise->get(x*frequency,y*frequency)*2 + offset) * exponents[i];
		value += weight * signal;
		weight *=  signal; // update the monotonically decreasing weight

		frequency *= lacunarity;
	}
	return (value-offset)/4.0;
}

void ptg::HybridFractal::onReSeed(unsigned int seed) {
	baseNoise->seed(seed);
}

void HybridFractal::initExponents() {
	exponents.clear();
	exponents.reserve(octaves);
	for(unsigned int i=0; i<octaves; i++){
		// compute spectral weight for each frequency */
		exponents.push_back(pow( lacunarity, -H*i ));
	}
}

}//namespace ptg

