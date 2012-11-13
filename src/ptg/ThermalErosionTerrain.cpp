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
	if(x == 0 || y == 0 || x == size - 1 || y == size - 1){
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
	for(int i = 0; i < neighbours; ++i){
		d[i] = height - h[i];
		if(d[i] > T){
			dTotal += d[i];
		}
	}
	if(dTotal == 0)return;

	float dMax = d[0]; //greatest of the di's
	for(int i = 1; i < neighbours; ++i){
		if(d[i] > dMax){
			dMax = d[i];
		}
	}

	const float c = 0.2; //greater values than 0.5 will probably cause oscillations

	float deltas[neighbours];
	for(int i = 0; i < neighbours; ++i){
		//note. if source != dest, we need to to do something because the cell may already be changed!!
		//the new heights
		deltas[i] = c * (dMax - T) * d[i] / dTotal;
	}

	destination.addToHeight(x-1, y, deltas[0]);
	destination.addToHeight(x+1, y, deltas[1]);
	destination.addToHeight(x, y-1, deltas[2]);
	destination.addToHeight(x, y+1, deltas[3]);

	destination.addToHeight(x, y, - c * (dMax - T));
}

//runs the entire heightmap through a single iteration
void doErosionStep(const float T, HeightMap& heightMap){
	const unsigned int size = heightMap.getSize();
	HeightMap deltaHeights(size); //accumulates changes for this step
	for(unsigned int x = 0; x < size; ++x){
		for(unsigned int y = 0; y < size; ++y){
			erodePoint(x, y, T, heightMap, deltaHeights); //do automata step for the given point
		}
	}

	//update the heightmap with the accumulated deltas
	for(unsigned int x = 0; x < size; ++x){
		for(unsigned int y = 0; y < size; ++y){
			heightMap.addToHeight(x,y, deltaHeights.getHeight(x,y));
		}
	}
}

} //anonymous namespace

namespace ptg {

ThermalErosionTerrain::ThermalErosionTerrain(Terrain* source):
	source(source),
	iterations(50),
	slope(0.7){
}

ThermalErosionTerrain::~ThermalErosionTerrain() {
}

helsing::HeightMap ThermalErosionTerrain::generateHeightMap(
		unsigned int gridPoints, float gridSpacing) {
	if(source == NULL){
		return helsing::HeightMap(gridPoints);
	}
	helsing::HeightMap sourceHeightMap = source->generateHeightMap(gridPoints, gridSpacing);

	const float T = slope;

	for(unsigned int i = 0; i < iterations; ++i){
		doErosionStep(T, sourceHeightMap);
	}

	return sourceHeightMap;
}

void ThermalErosionTerrain::setSource(Terrain* newSource) {
	source = newSource;
}

} // namespace ptg

