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
	const int size=resolution*33;
	helsing::HeightMap heightMap(size);

	return heightMap;
}

/** recursively modifies the given heightmap by displacing midpoints
 * @param heightMap The HeightMap to modify
 * @param width width of the heightMap, has to be a power of two + 1
 * @param offsetX X offset on heightMap
 * @param offsetY Y offset on heightMap
 */
void MidpointDisplacementTerrain::fillHeightMap(helsing::HeightMap* heightMap,
		uint32_t resolution, uint32_t offsetX, uint32_t offsetY) const {
	std::cout << "getting heightmap, ox: " << offsetX << " oy: " << offsetY << " resolution: " << resolution << std::endl;
	uint32_t half = resolution/2;
	float bl = heightMap->getHeight(offsetX, offsetY);
	float br = heightMap->getHeight(offsetX+resolution-1, offsetY);
	float tl = heightMap->getHeight(offsetX, offsetY+resolution-1);
	float tr = heightMap->getHeight(offsetX+resolution-1, offsetY+resolution-1);
	//srand(seed);
	float newHeight = (bl+br+tl+tr)/4.0 + displacement(resolution);
	heightMap->setHeight(offsetX+half,offsetY+half, newHeight);
	//midpoint without displacement
	heightMap->setHeight(offsetX+half, offsetY, (bl+br)/2.f + displacement(resolution));
	heightMap->setHeight(offsetX, offsetY+half, (bl+tl)/2.f+ displacement(resolution));
	heightMap->setHeight(offsetX+resolution-1, offsetY+half, (br+tr)/2.f+ displacement(resolution));
	heightMap->setHeight(offsetX+half, offsetY+resolution-1, (tl+tr)/2.f+ displacement(resolution));
	if(resolution>3){
		getQuad(bottomLeft).fillHeightMap(heightMap, half+1, offsetX, offsetY);
		getQuad(bottomRight).fillHeightMap(heightMap, half+1, offsetX+half, offsetY);
		getQuad(topLeft).fillHeightMap(heightMap, half+1, offsetX, offsetY+half);
		getQuad(topRight).fillHeightMap(heightMap, half+1, offsetX+half, offsetY+half);
	}
}


} /* namespace ptg */
