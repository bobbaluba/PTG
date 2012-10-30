/**
 * Terrain.h
 *
 * @date 23. okt. 2012
 * @author Johan Helsing
 *
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <ptg/Seedable.h>

#include <helsing/HeightMap.h>

namespace ptg {

/// @brief Interface for creating HeightMaps
class Terrain: public Seedable {
public:
	Terrain(unsigned int seed = 0):Seedable(seed){}
	virtual ~Terrain(){}
	/** @brief Generates a HeightMap
	 * @param gridPoints number of gridPoints in one direction, or "width" of the HeightMap
	 * @param gridSpacing gridpoints per unit in terrain coordinate system
	 */
	virtual helsing::HeightMap generateHeightMap(unsigned int gridPoints, float gridSpacing) = 0;
};

} //namespace ptg
#endif /* TERRAIN_H_ */

