/*
 * MidpointDisplacementTerrain.cpp
 *
 *  Created on: 23. okt. 2012
 *      Author: johan
 */

#include "MidpointDisplacementTerrain.h"
#include "QuadTree.h"

#include <cassert>

namespace ptg {

MidpointDisplacementTerrain::MidpointDisplacementTerrain(unsigned int seed) :
		Terrain(seed),
		amplitude(0.6){
}

MidpointDisplacementTerrain::~MidpointDisplacementTerrain() {

}

helsing::HeightMap MidpointDisplacementTerrain::generateHeightMap(unsigned int gridPoints, float resolution) {
	helsing::HeightMap heightMap(gridPoints);
	displaceHeightMap(QuadTree(getSeed()), &heightMap, gridPoints, 0,0);
	return heightMap;
}

void MidpointDisplacementTerrain::displaceHeightMap(QuadTree root,
		helsing::HeightMap* heightMap, uint32_t gridPoints, uint32_t offsetX,
		uint32_t offsetY) const {
	uint32_t half = gridPoints/2;
	float bl = heightMap->getHeight(offsetX, offsetY);
	float br = heightMap->getHeight(offsetX+gridPoints-1, offsetY);
	float tl = heightMap->getHeight(offsetX, offsetY+gridPoints-1);
	float tr = heightMap->getHeight(offsetX+gridPoints-1, offsetY+gridPoints-1);

	/// set the midpoints along the edges
	heightMap->setHeight(offsetX+half, offsetY, (bl+br)/2.f);
	heightMap->setHeight(offsetX, offsetY+half, (bl+tl)/2.f);
	heightMap->setHeight(offsetX+gridPoints-1, offsetY+half, (tr+br)/2.f);
	heightMap->setHeight(offsetX+half, offsetY+gridPoints-1, (tr+tl)/2.f);

	//find the average of the four corners
	float average = (bl+br+tl+tr)/4.0;


	//displace the midpoint
	srand(root.getSeed());
	float newHeight = average + displacement(static_cast<float>(gridPoints));
	heightMap->setHeight(offsetX+half,offsetY+half, newHeight);

	//make recursive calls if appropriate
	if(gridPoints>3){
		displaceHeightMap(root.getSubTree(QuadTree::bottomLeft), heightMap, half+1, offsetX, offsetY);
		displaceHeightMap(root.getSubTree(QuadTree::bottomRight), heightMap, half+1, offsetX+half, offsetY);
		displaceHeightMap(root.getSubTree(QuadTree::topLeft), heightMap, half+1, offsetX, offsetY+half);
		displaceHeightMap(root.getSubTree(QuadTree::topRight), heightMap, half+1, offsetX+half, offsetY+half);
	}
}

float MidpointDisplacementTerrain::displacement(float distance) const{
	return (rand()/float(RAND_MAX)-0.5)*distance*amplitude; //*resolution/flatness;
}

} /* namespace ptg */

