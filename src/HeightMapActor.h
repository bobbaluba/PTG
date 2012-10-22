/*
 * HeightMapActor.h
 *
 *  Created on: 27. sep. 2012
 *      Author: johan
 */

#ifndef HEIGHTMAPACTOR_H_
#define HEIGHTMAPACTOR_H_

#include "Actor.h"
#include "helsing/HeightMap.h"

class HeightMapActor: public Actor {
public:
	HeightMapActor(const helsing::HeightMap* heightMap);
	virtual ~HeightMapActor();
	virtual void draw();
private:
	const helsing::HeightMap * heightMap;
};

#endif /* HEIGHTMAPACTOR_H_ */
