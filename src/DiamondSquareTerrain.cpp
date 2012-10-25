/**
 * DiamondSquareTerrain.cpp
 *
 * @date 25. okt. 2012
 * @author Johan Klokkhammer Helsing
 */

#include "DiamondSquareTerrain.h"

#include <cassert>

using helsing::HeightMap;

namespace ptg {

DiamondSquareTerrain::DiamondSquareTerrain(unsigned int seed) :
		Terrain(seed),
		roughness(0.6){
}

DiamondSquareTerrain::~DiamondSquareTerrain() {
}

//this method iteratively generates a heightmap using the diamond square algorithm
helsing::HeightMap DiamondSquareTerrain::generateHeightMap(
		unsigned int gridPoints, float gridSpacing) {
	assert(helsing::isPowerOfTwo(gridPoints-1));
	HeightMap heightMap(gridPoints);

	for(int sideLength = gridPoints; sideLength>=3; sideLength=sideLength/2+1){
		int half = sideLength/2;
		//displace midpoints
		//this step is basically midpoint displacement
		for(unsigned int i=0; i<gridPoints-1; i+=sideLength-1){
			for(unsigned int j=0; j<gridPoints-1; j+=sideLength-1){
				float bl = heightMap.getHeight(i,j);
				float br = heightMap.getHeight(i+sideLength-1,j);
				float tl = heightMap.getHeight(i,j+sideLength-1);
				float tr = heightMap.getHeight(i+sideLength-1,j+sideLength-1);
				float average = (bl+br+tl+tr)/4;
				heightMap.setHeight(i+half, j+half, average+sideLength/gridPoints*8);

				heightMap.setHeight(i+half, j, (bl+br)/2);
				heightMap.setHeight(i, j+half, (tl+bl)/2);
				heightMap.setHeight(i+sideLength-1, j+half, (tr+br)/2);
				heightMap.setHeight(i+half, j+sideLength-1, (tl+tr)/2);
			}
		}

	}

	return heightMap;
}

float DiamondSquareTerrain::displacement(float distance) const{
	return (rand()/float(RAND_MAX)-0.5)*distance*roughness; //*resolution/flatness;
}

} /* namespace ptg */
