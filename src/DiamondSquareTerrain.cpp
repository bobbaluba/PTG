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

	for(int sideLength = gridPoints-1; sideLength>=2; sideLength/=2){
		int half = sideLength/2;
		//displace midpoints
		//this step is basically midpoint displacement
		for(unsigned int i=0; i<gridPoints/sideLength; i++){
			for(unsigned int j=0; j<gridPoints/sideLength; j++){
				float bl = heightMap.getHeight( i      * sideLength, j       * sideLength); //bottom left
				float br = heightMap.getHeight((i + 1) * sideLength, j       * sideLength); //bottom right
				float tl = heightMap.getHeight( i      * sideLength, (j + 1) * sideLength); //top left
				float tr = heightMap.getHeight((i + 1) * sideLength, (j + 1) * sideLength); //top right
				float average = (bl + br + tl + tr) / 4;
				heightMap.setHeight(i*sideLength+half, j*sideLength+half, average+displacement(sideLength));

				heightMap.setHeight(i*sideLength+half, j*sideLength,      (bl+br)/2); //bottom
				heightMap.setHeight(i*sideLength+half, (j+1)*sideLength,  (tl+tr)/2); //top
				heightMap.setHeight(i*sideLength     , j*sideLength+half, (tl+bl)/2); //left
				heightMap.setHeight((i+1)*sideLength , j*sideLength+half, (tr+br)/2); //right
			}

		}

	}

	return heightMap;
}

float DiamondSquareTerrain::displacement(float distance) const{
	return (rand()/float(RAND_MAX)-0.5)*distance*roughness; //*resolution/flatness;
}

} /* namespace ptg */
