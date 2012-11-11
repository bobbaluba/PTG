/**
 * @file MidpointDisplacementTerrain.cpp
 * @date 23. okt. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <ptg/MidpointDisplacementTerrain.hpp>

#include <cassert>

namespace ptg {

MidpointDisplacementTerrain::MidpointDisplacementTerrain(float gain, unsigned int seed) :
		Terrain(seed),
		amplitude(0.6),
		gain(gain){
}

MidpointDisplacementTerrain::~MidpointDisplacementTerrain() {

}

helsing::HeightMap MidpointDisplacementTerrain::generateHeightMap(unsigned int gridPoints, float resolution) {
	assert(helsing::isPowerOfTwo(gridPoints-1));
	helsing::HeightMap heightMap(gridPoints);

	//seed random generator
	srand(getSeed());
	float octaveAmplitude=amplitude*resolution;
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

				heightMap.setHeight(i*sideLength+half, j*sideLength,      (bl+br)/2); //bottom
				heightMap.setHeight(i*sideLength     , j*sideLength+half, (tl+bl)/2); //left
				if(j==currentGridSize-1)heightMap.setHeight(i*sideLength+half, (j+1)*sideLength,  (tl+tr)/2); //top
				if(i==currentGridSize-1)heightMap.setHeight((i+1)*sideLength , j*sideLength+half, (tr+br)/2); //right
			}
		}
		octaveAmplitude*=gain;
	}

	return heightMap;
}

float MidpointDisplacementTerrain::whiteNoise() const{
	return (rand()/float(RAND_MAX)-0.5);
}

} /* namespace ptg */

