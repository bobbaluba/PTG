/**
 * @file Clock.hpp
 * @date 20. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <string>
#include <ctime>

namespace helsing {

/** @brief Represents a stopwatch
 *
 * A clock cannot be stopped or started, only restated
 */
class Clock {
public:
	Clock():started(clock()){}
	void restart(){started = clock();}
	unsigned int getAsMilliseconds(){return (clock()-started)*1000/CLOCKS_PER_SEC;}
private:
	unsigned int started;
};


} // namespace helsing
#endif // CLOCK_HPP
