/*
 * PerlinNoise.h
 *
 *  Created on: 22. okt. 2012
 *      Author: johan
 *
 *  Two dimensional Perlin noise. As described by Ken Perlin in his talk on noise:
 *  	http://www.noisemachine.com/talk1/
 *
 *  = Memory Footprint =
 *  The noise function has a very relatively small memory footprint.
 *  It stores only SAMPLES gradients (8 bytes each) and a permutation table of SAMPLES size
 *
 *  = Complexity =
 *
 *  == Lookup ==
 *  In generalized Perlin noise, computation is n^2. Where n is the number of dimensions.
 *  Since we this is only a two dimensional implementation, n=2, and we have constant time lookup.
 *	O(1)
 *
 *  ==Initialization==
 *  Initialization is first order polynomial with SAMPLES
 *  O(SAMPLES) where samples is the number of stored gradients/size of the permutation table
 *
 *  Artifacts:
 *  	* The value of the noise will be zero on every whole number
 *  	* The noise will repeat after SAMPLES in either direction.
 */

#ifndef PERLINNOISE_H_
#define PERLINNOISE_H_

#include "Continuous2DSignal.h"

#include <helsing/Vec2.h>

class PerlinNoise: public Continuous2DSignal {
public:
	PerlinNoise(unsigned int seed = 0);
	virtual ~PerlinNoise();
	virtual float get(float x, float y);
private:
	/**
	 * hash function
	 *
	 * @return a number between 0 and SAMPLES-1
	 */
	unsigned int hash(int x, int y);
	float gridPointContribution(int x, int y, const helsing::Vec2& position);


	static const unsigned int SAMPLES = 256;
	std::array<unsigned int, SAMPLES> permutations; //holds indexes from 0 to SAMPLES in random order
	std::array<helsing::Vec2, SAMPLES> gradients; //holds random gradients of unit length
};

#endif /* PERLINNOISE_H_ */