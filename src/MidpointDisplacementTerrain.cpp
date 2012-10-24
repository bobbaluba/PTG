/*
 * MidpointDisplacementTerrain.cpp
 *
 *  Created on: 23. okt. 2012
 *      Author: johan
 */

#include "MidpointDisplacementTerrain.h"
#include "QuadTree.h"

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
 * @param root root node of the quadTree we are filling out
 * @param heightMap The HeightMap to modify
 * @param gridSize dimensions of the heightMap to fill out, has to be a power of two + 1
 * @param offsetX X offset on heightMap
 * @param offsetY Y offset on heightMap
 */
void MidpointDisplacementTerrain::fillHeightMap(QuadTree root,
		helsing::HeightMap* heightMap, uint32_t gridSize, uint32_t offsetX,
		uint32_t offsetY) const {
	uint32_t half = gridSize/2;
	float bl = heightMap->getHeight(offsetX, offsetY);
	float br = heightMap->getHeight(offsetX+gridSize-1, offsetY);
	float tl = heightMap->getHeight(offsetX, offsetY+gridSize-1);
	float tr = heightMap->getHeight(offsetX+gridSize-1, offsetY+gridSize-1);

	//find the average of the four corners
	float average = (bl+br+tl+tr)/4.0;

	//displace the midpoint
	srand(getSeed());
	float newHeight = average + displacement(static_cast<float>(gridSize));
	heightMap->setHeight(offsetX+half,offsetY+half, newHeight);

	//make recursive calls if appropriate
	if(gridSize>3){
		fillHeightMap(root.getSubTree(QuadTree::bottomLeft), heightMap, half+1, offsetX, offsetY);
		fillHeightMap(root.getSubTree(QuadTree::bottomRight), heightMap, half+1, offsetX+half, offsetY);
		fillHeightMap(root.getSubTree(QuadTree::topLeft), heightMap, half+1, offsetX, offsetY+half);
		fillHeightMap(root.getSubTree(QuadTree::topRight), heightMap, half+1, offsetX+half, offsetY+half);
	}
}

float MidpointDisplacementTerrain::displacement(float gridSize) {
	return 0;
}

} /* namespace ptg */

