/**
 * @file QuadTree.hpp
 * @date 29. aug. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <ptg/Seedable.hpp>

#include <helsing/HeightMap.hpp>

#include <array>

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
		topLeft=0, topRight, bottomLeft, bottomRight
	};
	QuadTree(unsigned int seed=0);
	QuadTree getSubTree(Corner corner) const;
};


} //namespace ptg
#endif /* QUAD_HPP */
