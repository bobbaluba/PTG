/**
 * @file Clock.hpp
 * @date 20. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <string>
#include <ctime>
#include <chrono>

namespace helsing {

/** @brief Represents a stopwatch
 *
 * A clock cannot be stopped or started, only restated
 */
class Clock {
public:
	explicit Clock():started(std::chrono::high_resolution_clock::now()){}
	void restart(){started = std::chrono::high_resolution_clock::now();}
	unsigned int getAsMilliseconds() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-started).count();
	}
private:
	std::chrono::high_resolution_clock::time_point started;
};


} // namespace helsing
#endif // CLOCK_HPP
