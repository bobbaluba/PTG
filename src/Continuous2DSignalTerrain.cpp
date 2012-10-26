/*
 * Continuous2DSignalTerrain.cpp
 *
 *  Created on: 26. okt. 2012
 *      Author: johan
 */

#include "Continuous2DSignalTerrain.h"

namespace ptg {

Continuous2DSignalTerrain::Continuous2DSignalTerrain(unsigned int seed):
	Terrain(seed),
	signal(NULL){
}

Continuous2DSignalTerrain::~Continuous2DSignalTerrain() {
}

helsing::HeightMap Continuous2DSignalTerrain::generateHeightMap(
		unsigned int gridPoints, float gridSpacing) {
	helsing::HeightMap heightMap(gridPoints);
	return heightMap;
}

} /* namespace ptg */

