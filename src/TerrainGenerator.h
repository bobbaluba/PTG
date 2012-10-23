/**
 * TerrainGenerator.h
 *
 * @date 23. okt. 2012
 * @author Johan Helsing
 *
 * @brief Interface for creating HeightMaps
 *
 */

#ifndef TERRAINGENERATOR_H_
#define TERRAINGENERATOR_H_

#include "Seedable.h"

#include "helsing/HeightMap.h"

class TerrainGenerator: public Seedable {
public:
	TerrainGenerator(unsigned int seed = 0):Seedable(seed){}
	virtual ~TerrainGenerator(){}
	/// Generates a HeightMap
	virtual helsing::HeightMap generate() = 0;
};

#endif /* TERRAINGENERATOR_H_ */
