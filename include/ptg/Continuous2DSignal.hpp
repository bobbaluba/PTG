/**
 * @file Continuous2DSignal.hpp
 * @date 22. okt. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef CONTINUOUS2DSIGNAL_HPP
#define CONTINUOUS2DSIGNAL_HPP

#include <ptg/Seedable.hpp>

namespace ptg {

/** @brief A continuous 2d signal.
 *
 * Any x or y should return a value.
 * Points with close x and y values, should have close output values
 * 
 * Useful in implicit procedural modeling techniques where the procedure answers
 * a query about a particular point.
 * 
 * This class inherits from Seedable because, most frequently, the signal will be
 * a noise function, or at least based on a noise function. I could have taken an
 * intermediate step, and created a subclass named Continuous2DNoise, or renamed
 * the class, but this would only increase code complexity, or create confusion
 * about 2DSignals that aren't noise.
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
