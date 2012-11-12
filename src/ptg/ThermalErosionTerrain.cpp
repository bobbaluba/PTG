/**
 * @file ThermalErosionTerrain.cpp
 * @date 12. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <ptg/ThermalErosionTerrain.hpp>

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

ThermalErosionTerrain::ThermalErosionTerrain(Terrain* source):
	source(source){
}

ThermalErosionTerrain::~ThermalErosionTerrain() {
}

helsing::HeightMap ThermalErosionTerrain::generateHeightMap(
		unsigned int gridPoints, float gridSpacing) {
	if(source==NULL){
		return helsing::HeightMap(gridPoints);
	}
	helsing::HeightMap sourceHeightMap = source->generateHeightMap(gridPoints, gridSpacing);
	helsing::HeightMap heightMap(gridPoints);

	return heightMap;
}

void ThermalErosionTerrain::setSource(Terrain* newSource) {
	source = newSource;
}

} // namespace ptg

