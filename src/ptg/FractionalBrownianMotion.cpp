/**
 * @file FractionalBrownianMotion.cpp
 * @date 27. okt. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <ptg/FractionalBrownianMotion.hpp>

namespace ptg {

FractionalBrownianMotion::FractionalBrownianMotion(unsigned int seed):
	Continuous2DSignal(seed),
	baseNoise(seed),
	octaves(7),
	gain(0.5){
}

FractionalBrownianMotion::~FractionalBrownianMotion() {
}

float FractionalBrownianMotion::get(float x, float y) {
	float amplitude=1;
	float frequency=1;
	float fbmSum=0;
	for(unsigned int i = 0; i < octaves; i++){
		fbmSum += baseNoise.get(x*frequency,y*frequency)*amplitude;
		amplitude *= gain;
		frequency *= 2;
	}
	return fbmSum;
}

void ptg::FractionalBrownianMotion::onReSeed(unsigned int seed) {
	baseNoise.seed(seed);
}

}//namespace ptg

