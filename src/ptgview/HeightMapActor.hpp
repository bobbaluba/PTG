/**
 * @file HeightMapActor.hpp
 * @date 27. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef HEIGHTMAPACTOR_HPP
#define HEIGHTMAPACTOR_HPP

#include "Actor.hpp"

#include <helsing/HeightMap.hpp>

class HeightMapActor: public Actor {
public:
	HeightMapActor(const helsing::HeightMap* heightMap);
	virtual ~HeightMapActor();
	virtual void draw();
private:
	const helsing::HeightMap * heightMap;
};

#endif /* HEIGHTMAPACTOR_HPP */
