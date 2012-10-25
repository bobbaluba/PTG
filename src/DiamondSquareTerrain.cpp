/*
 * DiamondSquareTerrain.cpp
 *
 *  Created on: 25. okt. 2012
 *      Author: johan
 */

#include "DiamondSquareTerrain.h"

using helsing::HeightMap;

namespace ptg {

DiamondSquareTerrain::DiamondSquareTerrain(unsigned int seed) : Terrain(seed) {
}

DiamondSquareTerrain::~DiamondSquareTerrain() {
}

helsing::HeightMap DiamondSquareTerrain::generateHeightMap(
		unsigned int gridPoints, float gridSpacing) {
	HeightMap heightMap(gridPoints);

}

} /* namespace ptg */
