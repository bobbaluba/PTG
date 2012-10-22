	/*
 * quad.h
 *
 *  Created on: 29. aug. 2012
 *      Author: johan
 */

#ifndef QUAD_H_
#define QUAD_H_

#include <array>
#include "helsing/HeightMap.h"

class Quad {
public:
	enum Corner{
		topLeft, topRight, bottomLeft, bottomRight
	};
	Quad(uint32_t seed=0);
	void fillHeightMap(helsing::HeightMap* heightMap, uint32_t resolution, uint32_t offsetX, uint32_t offsetY) const;
	Quad getQuad(Corner corner) const;
private:
	uint32_t seed;
};


#endif /* QUAD_H_ */
