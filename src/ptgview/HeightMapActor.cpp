/**
 * @file HeightMapActor.cpp
 * @date 27. sep. 2012
 * @author johan
 */

#include "HeightMapActor.hpp"
#include "Renderer.hpp"

using namespace helsing;

HeightMapActor::HeightMapActor(const HeightMap* heightMap) : heightMap(heightMap) {
}

HeightMapActor::~HeightMapActor() {
}

void HeightMapActor::draw() {
	Renderer::drawHeightMap(*heightMap);
}
