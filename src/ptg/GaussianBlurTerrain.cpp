/**
 * @file GaussianBlurTerrain.cpp
 * @date 9. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <ptg/GaussianBlurTerrain.hpp>

#include <cstdlib>

namespace {

float gaussian2D(float x, float y, float deviation){
	//as described on the wikipedia page for gaussian blur
	const float factor = 1.0/(2*helsing::pi()*deviation*deviation);
	const float exponent = -(x*x+y*y)/(2*deviation*deviation);
	return factor*exp(exponent);
}

} //anonymous namespace

namespace ptg {

GaussianBlurTerrain::GaussianBlurTerrain(Terrain* source):
	source(source){
}

GaussianBlurTerrain::~GaussianBlurTerrain() {
}

helsing::HeightMap GaussianBlurTerrain::generateHeightMap(
		unsigned int gridPoints, float gridSpacing) {
	if(source==NULL){
		return helsing::HeightMap(gridPoints);
	}

	helsing::HeightMap sourceHeightMap = source->generateHeightMap(gridPoints, gridSpacing);
	helsing::HeightMap heightMap(gridPoints);

	//pattern should probably be stored, and not created on every generation
	//but the overhead is small compared to the creation of a heigthmap, so I don't care too much
	const unsigned int patternSize = 5;
	const float deviation = float(patternSize-1)/2 / 3; //according to wikipedia, pixel contribution is insignificant
	                                           //when x>3*deviation, this means patternSize/2 < 3*deviation
	float pattern[patternSize][patternSize];
	for(unsigned int i = 0; i<patternSize; ++i){
		for(unsigned int j=0; j<patternSize; ++j){
			const float x = -float(patternSize-1)/2+i; //TODO floor!
			const float y = -float(patternSize-1)/2+j;
			pattern[i][j] = gaussian2D(x,y,deviation);
		}
	}

	const unsigned int size = sourceHeightMap.getSize();
	for(unsigned int x=0; x<size; ++x){
		for(unsigned int y=0; y<size; ++y){
			float newHeight = 0;
			for(unsigned int i=0; i<patternSize; ++i){
				for(unsigned int j=0; j<patternSize; ++j){
					if(x>=patternSize/2+i && y>=patternSize/2+j && x-patternSize/2+i<size && y-patternSize/2+j<size){
						newHeight += sourceHeightMap.getHeight(x-patternSize/2+i, y-patternSize/2+j) * pattern[i][j];
					}
				}
			}
			heightMap.setHeight(x,y,newHeight);
		}
	}
	return heightMap;
}

void GaussianBlurTerrain::setSource(Terrain* newSource) {
	source = newSource;
}

} // namespace ptg

