/*
 * quad.cpp
 *
 *  Created on: 30. aug. 2012
 *      Author: johan
 */


#include "QuadTree.h"

#include <cstdlib>
#include <iostream>

namespace ptg {

QuadTree::QuadTree(unsigned int seed)
		: Seedable(seed){
}

QuadTree QuadTree::getSubTree(Corner corner) const{
	int seed = getSeed() + corner;
	srand(seed);
	return QuadTree(rand());
}

} //namespace ptg
