/**
 * @file DiamondSquareTerrain.cpp
 * @date 25. okt. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <ptg/DiamondSquareTerrain.hpp>

#include <cassert>

using helsing::HeightMap;

namespace ptg {

DiamondSquareTerrain::DiamondSquareTerrain(float gain, unsigned int seed) :
		Terrain(seed),
		amplitude(0.6),
		gain(gain){
}

DiamondSquareTerrain::~DiamondSquareTerrain() {
}

//this method iteratively generates a heightmap using the diamond square algorithm
helsing::HeightMap DiamondSquareTerrain::generateHeightMap(
		unsigned int gridPoints, float gridSpacing) {
	assert(helsing::isPowerOfTwo(gridPoints-1));
	HeightMap heightMap(gridPoints);

	//seed random generator
	srand(getSeed());
	float octaveAmplitude=amplitude*gridSpacing;
	for(unsigned int sideLength = gridPoints-1; sideLength>=2; sideLength/=2){
		unsigned int half = sideLength/2;
		//displace midpoints
		unsigned int currentGridSize=gridPoints/sideLength;
		for(unsigned int i=0; i<currentGridSize; i++){
			for(unsigned int j=0; j<currentGridSize; j++){
				float bl = heightMap.getHeight( i      * sideLength, j       * sideLength); //bottom left
				float br = heightMap.getHeight((i + 1) * sideLength, j       * sideLength); //bottom right
				float tl = heightMap.getHeight( i      * sideLength, (j + 1) * sideLength); //top left
				float tr = heightMap.getHeight((i + 1) * sideLength, (j + 1) * sideLength); //top right
				float average = (bl + br + tl + tr) / 4;
				heightMap.setHeight(i*sideLength+half, j*sideLength+half, average+whiteNoise()*octaveAmplitude);//*sqrt(2));

				heightMap.setHeight(i*sideLength+half, j*sideLength,      (bl+br)/2+whiteNoise()*octaveAmplitude); //bottom
				heightMap.setHeight(i*sideLength     , j*sideLength+half, (tl+bl)/2+whiteNoise()*octaveAmplitude); //left
				if(j==sideLength)heightMap.setHeight(i*sideLength+half, (j+1)*sideLength,  (tl+tr)/2+whiteNoise()*octaveAmplitude); //top
				if(i==sideLength)heightMap.setHeight((i+1)*sideLength , j*sideLength+half, (tr+br)/2+whiteNoise()*octaveAmplitude); //right
			}
		}
		octaveAmplitude*=gain;
	}

	return heightMap;
}

float DiamondSquareTerrain::whiteNoise() const{
	return (rand()/float(RAND_MAX)-0.5);
}

} /* namespace ptg */
