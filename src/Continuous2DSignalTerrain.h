/*
 * Continuous2DSignalTerrain.h
 *
 *  Created on: 26. okt. 2012
 *      Author: johan
 */

#ifndef CONTINUOUS2DSIGNALTERRAIN_H_
#define CONTINUOUS2DSIGNALTERRAIN_H_

#include "Terrain.h"
#include "Continuous2DSignal.h"

namespace ptg {

class Continuous2DSignalTerrain: public ptg::Terrain {
public:
	Continuous2DSignalTerrain(unsigned int seed=0);
	virtual ~Continuous2DSignalTerrain();
	virtual void setSignal(Continuous2DSignal* signal){this->signal=signal;}
	virtual helsing::HeightMap generateHeightMap(unsigned int gridPoints, float gridSpacing);
private:
	Continuous2DSignal* signal;
};

} /* namespace ptg */
#endif /* CONTINUOUS2DSIGNALTERRAIN_H_ */
