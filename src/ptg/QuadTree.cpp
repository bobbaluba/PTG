/*
 * QuadTree.cpp
 *
 *  Created on: 30. aug. 2012
 *      Author: Johan Klokkhammer Helsing
 */


#include <ptg/QuadTree.hpp>

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
