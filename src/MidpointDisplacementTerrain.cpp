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

helsing::HeightMap MidpointDisplacementTerrain::generateHeightMap(unsigned int gridPoints, float resolution) {
	helsing::HeightMap heightMap(gridPoints);
	fillHeightMap(QuadTree(getSeed()), &heightMap, gridPoints, 0,0);
	return heightMap;
}

/** recursively modifies the given heightmap by displacing midpoints
 * @param root root node of the quadTree we are filling out
 * @param heightMap The HeightMap to modify
 * @param gridPoints dimensions of the heightMap to fill out, has to be a power of two + 1
 * @param offsetX X offset on heightMap
 * @param offsetY Y offset on heightMap
 */
void MidpointDisplacementTerrain::fillHeightMap(QuadTree root,
		helsing::HeightMap* heightMap, uint32_t gridPoints, uint32_t offsetX,
		uint32_t offsetY) const {
	uint32_t half = gridPoints/2;
	float bl = heightMap->getHeight(offsetX, offsetY);
	float br = heightMap->getHeight(offsetX+gridPoints-1, offsetY);
	float tl = heightMap->getHeight(offsetX, offsetY+gridPoints-1);
	float tr = heightMap->getHeight(offsetX+gridPoints-1, offsetY+gridPoints-1);

	//find the average of the four corners
	float average = (bl+br+tl+tr)/4.0;

	//displace the midpoint
	srand(getSeed());
	float newHeight = average + displacement(static_cast<float>(gridPoints));
	heightMap->setHeight(offsetX+half,offsetY+half, newHeight);

	//make recursive calls if appropriate
	if(gridPoints>3){
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

