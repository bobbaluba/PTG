/**
 * @file ThermalErosionTerrain.cpp
 * @date 12. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <ptg/ThermalErosionTerrain.hpp>

#include <cstdlib>

namespace {
using helsing::HeightMap;

//runs the cellular automata on a single point
void erodePoint(const unsigned int x, const unsigned int y, const float T, const HeightMap& source, HeightMap& destination){
	const unsigned int size = source.getSize();
	//for now, just skip erosion on edges
	if(x == 0 || y == 0 || x == size - 1 || y == size){
		return;
	}

	const float height = source.getHeight(x, y);

	const int neighbours = 4;
	//original height values
	const float h[neighbours] = {
			source.getHeight(x - 1, y), //we are using the Von Neumann pattern
			source.getHeight(x + 1, y),
			source.getHeight(x, y - 1),
			source.getHeight(x, y + 1)
	};

	float d[neighbours];
	float dTotal = 0; //sum of all di greater than T
	for(int i=0; i<neighbours; ++i){
		d[i] = height - h[i];
		if(d[i] > T){
			dTotal += d[i];
		}
	}

	float dMax = d[0]; //greatest of the di's
	for(int i = 1; i < neighbours; ++i){
		if(d[i] > dMax){
			dMax = d[i];
		}
	}

	const float c = 0.5; //greater values than 0.5 will probably cause oscillations

	float newHeights[neighbours];
	for(int i = 0; i < neighbours; ++i){
		//note. if source != dest, we need to to do something because the cell may already be changed!!
		//the new heights
		newHeights[i] = h[i] + c * (dMax-T) * d[i] / dTotal;
	}

	destination.setHeight(x-1, y, newHeights[0]);
	destination.setHeight(x+1, y, newHeights[1]);
	destination.setHeight(x, y-1, newHeights[2]);
	destination.setHeight(x, y+1, newHeights[3]);

	destination.setHeight(x, y, height - c * (dMax-T));
}

//runs the entire heightmap throug a single iteration
void doErosionStep(const float T, HeightMap& heightMap){
	const unsigned int size = heightMap.getSize();
	for(unsigned int x = 0; x < size; ++x){
		for(unsigned int y = 0; y < size; y++){
			erodePoint(x, y, T, heightMap, heightMap); //apply erosion directly on the heightMap
		}
	}
}

} //anonymous namespace

namespace ptg {

ThermalErosionTerrain::ThermalErosionTerrain(Terrain* source):
	source(source),
	steps(8){
}

ThermalErosionTerrain::~ThermalErosionTerrain() {
}

helsing::HeightMap ThermalErosionTerrain::generateHeightMap(
		unsigned int gridPoints, float gridSpacing) {
	if(source == NULL){
		return helsing::HeightMap(gridPoints);
	}
	helsing::HeightMap sourceHeightMap = source->generateHeightMap(gridPoints, gridSpacing);
	helsing::HeightMap heightMap(gridPoints);

	const float T = 1.0 / gridPoints;

	for(unsigned int i = 0; i < steps; ++i){
		doErosionStep(T, heightMap);
	}

	return heightMap;
}

void ThermalErosionTerrain::setSource(Terrain* newSource) {
	source = newSource;
}

} // namespace ptg

