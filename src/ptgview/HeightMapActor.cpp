/*
 * HeightMapActor.cpp
 *
 *  Created on: 27. sep. 2012
 *      Author: johan
 */

#include "HeightMapActor.hpp"
#include "Renderer.hpp"

using namespace helsing;
using namespace ptg;

HeightMapActor::HeightMapActor(const HeightMap* heightMap) : heightMap(heightMap) {
}

HeightMapActor::~HeightMapActor() {
}

void HeightMapActor::draw() {
	Renderer::drawHeightMap(*heightMap);
}