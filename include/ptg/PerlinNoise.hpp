/**
 * @file PerlinNoise.hpp
 * @date 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef PERLINNOISE_HPP
#define PERLINNOISE_HPP

#include <ptg/Continuous2DSignal.hpp>

#include <helsing/math/Vec2.hpp>

namespace ptg {
/** @brief Two dimensional Perlin noise.
 *
 * Two dimensional Perlin noise. As described by Ken Perlin in his talk on noise:
 *     http://www.noisemachine.com/talk1/
 *
 * Memory Footprint
 * ----------------
 *
 * The noise function has a very relatively small memory footprint.
 * It stores only SAMPLES gradients (8 bytes each) and a permutation table of SAMPLES size
 *
 * Complexity
 * ----------
 *
 * **Lookup:**
 * In generalized Perlin noise, computation is n^2. Where n is the number of dimensions.
 * Since we this is only a two dimensional implementation, n=2, and we have constant time lookup.
 *
 *     O(1)
 *
 *
 * **Initialization:**
 * Initialization is first order polynomial with SAMPLES
 *
 *     O(SAMPLES)
 *
 * where samples is the number of stored gradients/size of the permutation table
 *
 * Artifacts:
 *  * The value of the noise will be zero on every whole number
 *  * The noise will repeat after SAMPLES in either direction.
 */
class PerlinNoise: public Continuous2DSignal {
public:
	explicit PerlinNoise(unsigned int seed = 0);
	virtual ~PerlinNoise();
	virtual float get(float x, float y);
	virtual void onReSeed(unsigned int seed);
private:
	/**
	 * hash function
	 * is inlined to improve performance
	 *
	 * @return a number between 0 and SAMPLES-1
	 */
	unsigned int hash(int x, int y) {
		//perlins original implementation used a performance optimization trick where
		//he exploited byte overflow as an automatic modulus function. This requires samples=256
		//another trick is to use a bit mask, although this has a less strict requirement, it still
		//requires samples to be a power of two. I used modulo here for modifiability and readability purposes
		return permutations[(y+permutations[x%SAMPLES])%SAMPLES];
	}
	void init(); //helper function, the same stuff should happen on instantiation and reseeding

	static const unsigned int SAMPLES = 256;
	std::array<unsigned int, SAMPLES> permutations; //holds indexes from 0 to SAMPLES in random order
	std::array<helsing::Vec2, SAMPLES> gradients; //holds random gradients of unit length
};

} //namespace ptg
#endif /* PERLINNOISE_HPP */
