/*
 * Continuous2DSignalTerrain.hpp
 *
 *  Created on: 26. okt. 2012
 *      Author: Johan Klokkhammer Helsing
 */

#ifndef CONTINUOUS2DSIGNALTERRAIN_H_
#define CONTINUOUS2DSIGNALTERRAIN_H_

#include <ptg/Terrain.hpp>
#include <ptg/Continuous2DSignal.hpp>

namespace ptg {

class Continuous2DSignalTerrain: public ptg::Terrain {
public:
	Continuous2DSignalTerrain(unsigned int seed=0);
	virtual ~Continuous2DSignalTerrain();
	virtual void setSignal(Continuous2DSignal* signal);
	virtual helsing::HeightMap generateHeightMap(unsigned int gridPoints, float gridSpacing);
	virtual void onReSeed(unsigned int seed);
	virtual void setAmplitude(float amplitude){this->amplitude=amplitude;}
private:
	Continuous2DSignal* signal;
	float amplitude;
};

} /* namespace ptg */
#endif /* CONTINUOUS2DSIGNALTERRAIN_H_ */