/**
 * @file RidgedMultiFractal.cpp
 * @date 12. nov. 2012
 * @author Johan Klokkhammer Helsing
 *
 * inspired by:
 * http://www.kenmusgrave.com/Old_Stuff/folders/texturingandmodeling/CODE/MUSGRAVE/CLOUD/fractal.c
 */

#include <ptg/RidgedMultiFractal.hpp>

#include <cstdlib>
#include <cmath>

namespace ptg {

RidgedMultiFractal::RidgedMultiFractal(unsigned int seed):
	Continuous2DSignal(seed),
	baseNoise(NULL),
	octaves(7),
	lacunarity(2),
	offset(1.0),
	H(0.25),
	threshold(0.9){
	initExponents();
}

RidgedMultiFractal::~RidgedMultiFractal() {
	initExponents();
}

float RidgedMultiFractal::get(float x, float y) {
	//copied from hybrid multi fractal
	float frequency=1;

	//compute first octave
	float signal = baseNoise->get(x*frequency, y*frequency);
	signal = fabs(signal);
	signal = offset - signal;
	signal *= signal; //square signal to increase sharpness

	float result = signal;
 	frequency = lacunarity;
	float weight = 1;
	for(unsigned int i = 1; weight>0.001 && i < octaves; i++){
		weight = signal*threshold; //weight depends on strength of previous signal

		signal = baseNoise->get(x*frequency,y*frequency);
		signal = fabs(signal);
		signal = offset - signal;
		signal *= signal;
		signal *= weight;
		result += signal * exponents[i];

		if(weight>1)weight=1;
		if(weight<0)weight=0;
		result += weight * signal;
		weight *=  signal; // update the monotonically decreasing weight

		frequency *= lacunarity;
	}
	return result;
}

void ptg::RidgedMultiFractal::onReSeed(unsigned int seed) {
	baseNoise->seed(seed);
}

void RidgedMultiFractal::initExponents() {
	exponents.clear();
	exponents.reserve(octaves);
	for(unsigned int i=0; i<octaves; i++){
		// compute spectral weight for each frequency */
		exponents.push_back(pow( lacunarity, -H*i ));
	}
}

}//namespace ptg

