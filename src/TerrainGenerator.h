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

class TerrainGenerator: public Seedable {
public:
	TerrainGenerator(unsigned int seed):Seedable(seed){}
	virtual ~TerrainGenerator(){}
	/// Generates a HeightMap
	virtual helsing::HeightMap generate();
};

#endif /* TERRAINGENERATOR_H_ */
