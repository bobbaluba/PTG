/*
 * quad.cpp
 *
 *  Created on: 30. aug. 2012
 *      Author: johan
 */


#include "quad.h"

#include <cstdlib>
#include <iostream>

inline QuadTree::Corner getCorner(uint32_t a){
	return QuadTree::Corner(a%4);
}

QuadTree::QuadTree(uint32_t seed)
		:seed(seed){
}

QuadTree QuadTree::getSubTree(Corner corner) const{
	srand(seed+corner);
	return QuadTree(rand());
}
