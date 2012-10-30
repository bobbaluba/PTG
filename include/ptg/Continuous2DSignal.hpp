/**
 * Continous2DSignal.hpp
 *
 * @date 22. okt. 2012
 * @author Johan Klokkhammer Helsing
 *
 */

#ifndef CONTINUOUS2DSIGNAL_HPP
#define CONTINUOUS2DSIGNAL_HPP

#include <ptg/Seedable.hpp>

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

	/** Compute the signal value at the given point
	 * @return signal value
	 */
	virtual float get(float x, float y) = 0;
};

} //namespace ptg
#endif //CONTINOUS2DSIGNAL_HPP
