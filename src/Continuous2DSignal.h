/*
 * Continous2DSignal.h
 *
 *  Created on: 22. okt. 2012
 *      Author: johan
 *
 */

#ifndef CONTINOUS2DSIGNAL_H_
#define CONTINUOUS2DSIGNAL_H_

#include "Seedable.h"

namespace ptg {

/** @brief A continuous 2d signal.
 *
 * Any x or y should return a value.
 * Points with close x and y values, should have close output values
 */
class Continuous2DSignal: public Seedable {
public:
	explicit Continuous2DSignal(unsigned int seed = 0);
	virtual ~Continuous2DSignal();
	/// @return signal value at the given point
	virtual float get(float x, float y) = 0;
};

}// namespace ptg
#endif /* CONTINOUS2DSIGNAL_H_ */
