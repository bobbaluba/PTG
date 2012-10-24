/*
 * MidpointDisplacementTerrain.cpp
 *
 *  Created on: 23. okt. 2012
 *      Author: johan
 */

#include "MidpointDisplacementTerrain.h"

namespace ptg {

MidpointDisplacementTerrain::MidpointDisplacementTerrain(unsigned int seed) :
		Terrain(seed) {
}

MidpointDisplacementTerrain::~MidpointDisplacementTerrain() {

}

helsing::HeightMap MidpointDisplacementTerrain::generate(float resolution) {
	return helsing::HeightMap(resolution);
}

} /* namespace ptg */
