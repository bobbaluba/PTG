/*
 * HeightMap.h
 *
 * \date 2012
 * \author Johan Helsing
 */

#ifndef HEIGHTMAP_H_
#define HEIGHTMAP_H_

#include "helsing/hmath.h"
#include "helsing/Drawable.h"

namespace helsing {

class HeightMap {
public:
	HeightMap(uint32_t size);
	HeightMap(const float heights[], const uint32_t size);
	virtual ~HeightMap();
	virtual uint32_t getSize() const {return size;}
	virtual const helsing::Vec4 getNormal(int x, int z) const;
	virtual const helsing::Vec4 getPoint(uint32_t x, uint32_t z) const;
	virtual float getHeight(uint32_t x, uint32_t y) const {return heights[x+y*size];}
	virtual void setHeight(uint32_t x, uint32_t y, float h){heights[x+y*size]=h;}
private:
	float *heights;
	uint32_t size;
};

}

#endif
