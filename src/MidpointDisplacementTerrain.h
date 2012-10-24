/*
 * MidpointDisplacementTerrain.h
 *
 * @date 2012
 * @author Johan Helsing
 *
 */

#ifndef MIDPOINTDISPLACEMENTTERRAIN_H_
#define MIDPOINTDISPLACEMENTTERRAIN_H_

#include "Terrain.h"

namespace ptg {

/** @brief Generates terrain using the midpoint displacement algorithm
 *
 * Algorithm
 * ---------
 * Recur
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
 *     O(WIDTH^2)
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
class MidpointDisplacementTerrain : public Terrain {
public:
	MidpointDisplacementTerrain(unsigned int seed = 0);
	virtual ~MidpointDisplacementTerrain(){}
	virtual helsing::HeightMap generate(float resolution);
};

} /* namespace ptg */
#endif /* MIDPOINTDISPLACEMENTTERRAIN_H_ */