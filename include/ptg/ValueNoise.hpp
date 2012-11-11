/**
 * @file ValueNoise.hpp
 * @date 11. nov 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef VALUENOISE_HPP
#define VALUENOISE_HPP

#include <ptg/Continuous2DSignal.hpp>

#include <helsing/math/Vec2.hpp>

namespace ptg {
/** @brief Two dimensional value noise.
 *
 * Memory Footprint
 * ----------------
 * Rather big. For the alorithm to be efficient, the values must be stored.
 *
 *     THETA(SAMPLES^2)
 *
 * Complexity
 * ----------
 * Same as Perlin Noise //TODO elaborate here
 *
 * Artifacts
 * ---------
 *  * will show patterns that align with the axes.
 *  * The noise will repeat after SAMPLES in either direction.
 */
class ValueNoise: public Continuous2DSignal {
public:
	ValueNoise(unsigned int seed = 0);
	virtual ~ValueNoise();
	virtual float get(float x, float y);
	virtual void onReSeed(unsigned int seed);
private:
	void init(); //helper function, the same stuff should happen on construction and reseeding
	float getSample(unsigned int x, unsigned int y){
		x%=SAMPLES;
		y%=SAMPLES;
		return samples[x+y*SAMPLES];
	}
	static const unsigned int SAMPLES = 256; //The width of the sample array
	std::array<float, SAMPLES*SAMPLES> samples; //holds indexes from 0 to SAMPLES in random order
};

} //namespace ptg
#endif // VALUENOISE_HPP
