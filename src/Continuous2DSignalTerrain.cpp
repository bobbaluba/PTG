/*
 * Continuous2DSignalTerrain.cpp
 *
 *  Created on: 26. okt. 2012
 *      Author: johan
 */

#include "Continuous2DSignalTerrain.h"

#include <cstdlib> // for NULL

namespace ptg {

Continuous2DSignalTerrain::Continuous2DSignalTerrain(unsigned int seed):
	Terrain(seed),
	signal(NULL),
	amplitude(0.6){
}

Continuous2DSignalTerrain::~Continuous2DSignalTerrain() {
}


void Continuous2DSignalTerrain::setSignal(Continuous2DSignal* signal) {
	this->signal=signal;
}

helsing::HeightMap Continuous2DSignalTerrain::generateHeightMap(
		unsigned int gridPoints, float gridSpacing) {
	helsing::HeightMap heightMap(gridPoints);

	if(signal == NULL){
		return heightMap; //if there's no signal, simply return a flat HeightMap
	}

	for(unsigned int i=0; i<gridPoints; ++i){
		for(unsigned int j=0; j<gridPoints; ++j){
			heightMap.setHeight(i,j, signal->get(i/gridSpacing, j/gridSpacing)*gridSpacing*amplitude); //TODO GRIDSPACING?
		}
	}
	return heightMap;
}

void Continuous2DSignalTerrain::onReSeed(unsigned int seed) {
	if(signal!=NULL){
		signal->seed(getSeed());
	}
}

} /* namespace ptg */
