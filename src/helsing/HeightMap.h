/**
 * HeightMap.h
 *
 * @date 2012
 * @author Johan Helsing
 *
 * A HeightMap is a two dimensional grid of float values
 *
 */

#ifndef HEIGHTMAP_H_
#define HEIGHTMAP_H_

#include "helsing/hmath.h"
#include "helsing/Drawable.h"

namespace helsing {

class HeightMap {
public:
	/// @param size width and height of the heightmap
	HeightMap(uint32_t size);

	/// Initialize a heightmap by copying an array of floats
	HeightMap(const float heights[], const uint32_t size);

	virtual ~HeightMap();

	/// @return the width/height of the heightmap
	virtual uint32_t getSize() const {return size;}

	/// @return normal of the gridpoints, assuming distance between gridpoints is 1
	virtual const helsing::Vec4 getNormal(int x, int z) const;

	/// @return position of the grid point, assuming distance between gridpoints is 1
	virtual const helsing::Vec4 getPoint(uint32_t x, uint32_t z) const;

	/// @return height at the given grid coordinate
	virtual float getHeight(uint32_t x, uint32_t y) const {return heights[x+y*size];}

	/// Sets the height at the given grid coordinate
	virtual void setHeight(uint32_t x, uint32_t y, float h){heights[x+y*size]=h;}

private:
	float *heights;
	uint32_t size;
};

}

#endif
