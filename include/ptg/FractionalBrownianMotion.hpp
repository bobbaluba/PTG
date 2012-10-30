/*
 * FractionalBrownianMotion.hpp
 *
 *  Created on: 27. okt. 2012
 *      Author: Johan Klokkhammer Helsing
 */

#ifndef FRACTIONALBROWNIANMOTION_H_
#define FRACTIONALBROWNIANMOTION_H_

#include <ptg/Continuous2DSignal.hpp>
#include <ptg/PerlinNoise.hpp>

namespace ptg {

class FractionalBrownianMotion: public ptg::Continuous2DSignal {
public:
	FractionalBrownianMotion(unsigned int seed=0);
	virtual ~FractionalBrownianMotion();
	virtual float get(float x, float y);
	virtual void onReSeed(unsigned int seed);
private:
	PerlinNoise baseNoise;
};

} /* namespace ptg */
#endif /* FRACTIONALBROWNIANMOTION_H_ */
