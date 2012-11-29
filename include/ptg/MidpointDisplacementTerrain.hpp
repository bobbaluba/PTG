/**
 * @file MidpointDisplacementTerrain.hpp
 * @date 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef MIDPOINTDISPLACEMENTTERRAIN_HPP
#define MIDPOINTDISPLACEMENTTERRAIN_HPP

#include <ptg/Terrain.hpp>

namespace ptg {

/** @brief Generates terrain using the midpoint displacement algorithm
 *
 * Algorithm
 * ---------
 * Recursive algorithm. The displacement of each point depends on the displacement of the corners on
 * the level above.
 *
 * Memory footprint
 * ----------------
 * The algorithm has an extremely small memory footprint, only a single number is needed
 * to seed the random generator.
 *
 * Complexity
 * ----------
 * All gridpoints are visited exactly once, each point use constant time, making the complexity
 *
 *     THETA(WIDTH^2)
 *
 * Limitations and Artifacts
 * -------------------------
 * The algorithm creates obvious artifacts in a square like pattern.
 *
 * The width of the terrain has to be 2^n+1 where n is a positive integer
 *
 * Unless a bi-directional pseudo-random number generator is used,
 * the maximum level of detail or the maximum area the terrain covers are bounded.
 */
class MidpointDisplacementTerrain: public Terrain {
public:
	explicit MidpointDisplacementTerrain(float gain=0.5, unsigned int seed = 0);
	virtual ~MidpointDisplacementTerrain();
	virtual helsing::HeightMap generateHeightMap(unsigned int gridPoints, float resolution);
	virtual void setAmplitude(float amplitude){
		this->amplitude=amplitude;
	}
	virtual float getAmplitude() const{
		return amplitude;
	}
	virtual void setGain(float gain){this->gain=gain;}
private:
	///create noise between -0.5 and 0.5
	float whiteNoise() const;
	float amplitude;
	float gain;
};

} /* namespace ptg */
#endif /* MIDPOINTDISPLACEMENTTERRAIN_HPP */
