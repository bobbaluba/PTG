/**
 * Terrain.h
 *
 * @date 23. okt. 2012
 * @author Johan Helsing
 *
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "Seedable.h"

#include "helsing/HeightMap.h"

namespace ptg {

/// @brief Interface for creating HeightMaps
class Terrain: public Seedable {
public:
	Terrain(unsigned int seed = 0):Seedable(seed){}
	virtual ~Terrain(){}
	/** @brief Generates a HeightMap
	 * @param resolution gridpoints per unit in terrain coordinate system
	 */
	virtual helsing::HeightMap generate(float resolution) = 0;
};

} //namespace ptg
#endif /* TERRAIN_H_ */

