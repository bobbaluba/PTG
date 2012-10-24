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

#include "Seedable.h"

namespace ptg {

/**
 * This is a collection of functions useful functions for deterministically calculating
 * seeds for different portions of a two dimensional area.
 *
 * Until I implement a bi-directional random number generator, this function can
 * only calculate sub-trees, and not parents or siblings
 *
 */
class QuadTree : public Seedable {
public:
	enum Corner{
		topLeft, topRight, bottomLeft, bottomRight
	};
	QuadTree(unsigned int seed=0);
	QuadTree getSubTree(Corner corner) const;
};


} //namespace ptg
#endif /* QUAD_H_ */
