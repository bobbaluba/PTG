	/*
 * quad.h
 *
 *  Created on: 29. aug. 2012
 *      Author: johan
 */

#ifndef QUAD_H_
#define QUAD_H_

#include <array>
#include <helsing/HeightMap.h>

/**
 * This is a collection of functions useful functions for deterministically calculating
 * seeds for different portions of a two dimensional area.
 *
 * Until I implement a bi-directional random number generator, this function can
 * only calculate sub-trees, and not parents or siblings
 *
 */
class QuadTree {
public:
	enum Corner{
		topLeft, topRight, bottomLeft, bottomRight
	};
	QuadTree(uint32_t seed=0);
	void fillHeightMap(helsing::HeightMap* heightMap, uint32_t resolution, uint32_t offsetX, uint32_t offsetY) const;
	QuadTree getSubTree(Corner corner) const;
private:
	uint32_t seed;
};


#endif /* QUAD_H_ */
