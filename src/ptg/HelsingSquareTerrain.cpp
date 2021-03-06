/**
 * @file HelsingSquareTerrain.cpp
 * @date 11. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <ptg/HelsingSquareTerrain.hpp>

#include <cassert>

using helsing::HeightMap;

namespace ptg {

HelsingSquareTerrain::HelsingSquareTerrain(float gain, unsigned int seed) :
		Terrain(seed),
		amplitude(0.6),
		gain(gain){
}

HelsingSquareTerrain::~HelsingSquareTerrain() {
}

//this method iteratively generates a heightmap using the helsing square algorithm
helsing::HeightMap HelsingSquareTerrain::generateHeightMap(
		unsigned int gridPoints, float gridSpacing) {
	assert(helsing::isPowerOfTwo(gridPoints-1));
	HeightMap heightMap(gridPoints);

	//seed random generator
	srand(getSeed());
	float octaveAmplitude=amplitude*gridSpacing;
	for(unsigned int sideLength = gridPoints-1; sideLength>=2; sideLength/=2){
		unsigned int half = sideLength/2;
		//displace midpoints
		//this step is basically midpoint displacement
		unsigned int currentGridSize=gridPoints/sideLength;
		for(unsigned int i=0; i<currentGridSize; i++){
			for(unsigned int j=0; j<currentGridSize; j++){
				float bl = heightMap.getHeight( i      * sideLength, j       * sideLength); //bottom left
				float br = heightMap.getHeight((i + 1) * sideLength, j       * sideLength); //bottom right
				float tl = heightMap.getHeight( i      * sideLength, (j + 1) * sideLength); //top left
				float tr = heightMap.getHeight((i + 1) * sideLength, (j + 1) * sideLength); //top right
				float average = (bl + br + tl + tr) / 4;
				heightMap.setHeight(i*sideLength+half, j*sideLength+half, average+whiteNoise()*octaveAmplitude*sqrt(2));
			}
		}

		//helsing step
		//this grid is the double size of that above
		currentGridSize=currentGridSize*2+1;
		for(unsigned int i=0; i<currentGridSize; i++){
			for(unsigned int j=0; j<currentGridSize; j++){
				//we are going to calculate displacement for every second point on this grid, starting with the second
				// + x + x + // we are displacing the x'es in this pattern
				// x + x + x // the pluses are the points that already have a height
				// + x + x +
				// x + x + x
				// + x + x +
				unsigned int index = i*currentGridSize+j;
				if (index%2==0){ //we have a plus, a point that already has been displaced
					continue; //skip to next point
				}
				float average = 0;
				unsigned int neighbours = 0; // number of points used to make the average
				if(i>0) {
					++neighbours;
					average += heightMap.getHeight((i-1)*half, j*half);
				}
				if(i+1<currentGridSize) {
					++neighbours;
					average += heightMap.getHeight((i+1)*half, j*half);
				}
				if(j>0) {
					++neighbours;
					average += heightMap.getHeight(i*half, (j-1)*half);
				}
				if(j+1<currentGridSize){
					++neighbours;
					average += heightMap.getHeight(i*half, (j+1)*half);
				}
				average /= neighbours;

				heightMap.setHeight(i*half, j*half, average+whiteNoise()*octaveAmplitude);

			}
		}
		octaveAmplitude*=gain;
	}

	return heightMap;
}

float HelsingSquareTerrain::whiteNoise() const{
	return (rand()/float(RAND_MAX)-0.5);
}

} /* namespace ptg */
