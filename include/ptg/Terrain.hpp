/**
 * @file Terrain.hpp
 * @date 23. okt. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <ptg/Seedable.hpp>

#include <helsing/HeightMap.hpp>

namespace ptg {

/// @brief Interface for creating HeightMaps
class Terrain: public Seedable {
public:
	explicit Terrain(unsigned int seed = 0):Seedable(seed){}
	virtual ~Terrain(){}
	/** @brief Generates a HeightMap
	 * @param gridPoints number of gridPoints in one direction, or "width" of the HeightMap
	 * @param gridSpacing gridpoints per unit in terrain coordinate system
	 */
	virtual helsing::HeightMap generateHeightMap(unsigned int gridPoints, float gridSpacing) = 0;
};

} //namespace ptg
#endif /* TERRAIN_HPP */

