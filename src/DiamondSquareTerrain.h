/*
 * DiamondSquareTerrain.h
 *
 *  Created on: 25. okt. 2012
 *      Author: johan
 */

#ifndef DIAMONDSQUARETERRAIN_H_
#define DIAMONDSQUARETERRAIN_H_

#include <Terrain.h>

namespace ptg {

/** @brief Terrain generated using the diamond square algorithm
 *
 * Limitations
 * -----------
 * Size of the grid has to be 2^n+1
 *
 */
class DiamondSquareTerrain: public ptg::Terrain {
public:
	explicit DiamondSquareTerrain(unsigned int seed=0);
	virtual ~DiamondSquareTerrain();
	virtual helsing::HeightMap generateHeightMap(unsigned int gridPoints, float gridSpacing);
};

} /* namespace ptg */
#endif /* DIAMONDSQUARETERRAIN_H_ */
