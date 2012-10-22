/*
 * quad.cpp
 *
 *  Created on: 30. aug. 2012
 *      Author: johan
 */


#include "quad.h"

#include <cstdlib>
#include <iostream>

inline uint32_t parent(uint32_t a){
	return a/4;
}

inline uint32_t child(uint32_t a, Quad::Corner corner){
	return a*4+corner;
}

inline uint32_t sibling(uint32_t a, Quad::Corner corner){
	return child(parent(a), corner);
}

inline Quad::Corner getCorner(uint32_t a){
	return Quad::Corner(a%4);
}

Quad::Quad(uint32_t seed)
		:seed(seed){

}

inline float displacement(float resolution) {
	const float roughness = 0.6f;
	return (rand()/float(RAND_MAX)-0.5)*resolution*roughness; //*resolution/flatness;
}

void Quad::fillHeightMap(helsing::HeightMap* heightMap, uint32_t resolution, uint32_t offsetX, uint32_t offsetY) const {
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

Quad Quad::getQuad(Corner corner) const{
	return Quad(seed+corner);
}
