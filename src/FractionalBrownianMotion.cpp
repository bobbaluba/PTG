/*
 * FractionalBrownianMotion.cpp
 *
 *  Created on: 27. okt. 2012
 *      Author: johan
 */

#include "FractionalBrownianMotion.h"

namespace ptg {

FractionalBrownianMotion::FractionalBrownianMotion(unsigned int seed):
	Continuous2DSignal(seed),
	baseNoise(seed){
}

FractionalBrownianMotion::~FractionalBrownianMotion() {
}

float FractionalBrownianMotion::get(float x, float y) {
	const int octaves=9;
	float amplitude=1;
	float frequency=1;
	float fbmSum=0;
	for(int i=0; i<octaves; i++){
		fbmSum += baseNoise.get(x*frequency,y*frequency)*amplitude;
		amplitude/=2;
		frequency*=2;
	}
	return fbmSum;
}

void ptg::FractionalBrownianMotion::onReSeed(unsigned int seed) {
	baseNoise.seed(seed);
}

}//namespace ptg

