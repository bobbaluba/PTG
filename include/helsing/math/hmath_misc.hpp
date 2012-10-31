/**
 * @file hmath_misc.hpp
 * @ingroup math
 * @date 24. okt. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef HMATH_MISC_HPP
#define HMATH_MISC_HPP

#include <cmath>

namespace helsing {

//TODO switch to constexpr!!
inline double pi() { return std::atan(1)*4; }

/** @brief Usable AlmostEqual function
 * @ingroup math
 *
 * Could be implemented better so it doesn't need epsilon.
 * An implementation that depends on bit error would be better.
 *
 * @return true if the difference between the values is below epsilon
 */
inline bool almostEqual(float a, float b, float epsilon){
	return std::abs(a-b) < epsilon;
}

/** @brief Checks if the given integer is a number of two
 * @ingroup math
 */
inline bool isPowerOfTwo(int x){
	return ( (x > 0) && ((x & (x - 1)) == 0) );
}

/** @brief used to interpolate smoothly between zero and one.
 * @ingroup math
 *
 *  It has the following properties
 *  * 0 at t=0
 *  * 1 at t=1
 *  * It is continuous
 *  * First derivative is zero at both 0 and 1.
 */
inline float smoothStep(float t){
	//3T^2-2T^3
	return t * t * (3 - 2 * t);
}

/** @brief used to interpolate more smoothly between zero and one.
 * @ingroup math
 * This implementation is as suggested by Ken Perlin.
 * It has the following properties
 *  * 0 at t=0
 *  * 1 at t=1
 *  * It is continuous
 *  * First and second derivative is zero at both 0 and 1.
 */
inline float smootherStep(float t){
	//6T^5-15T^4+10T^3
	return t*t*t*(t*(t*6-15) + 10);
}

/** @brief Wrapper class to easily convert between radians and degrees.
 * @ingroup math
 *
 * The class uses radians to store the angle internally.
 */
class Angle {
public:
	/// @brief create a new Angle using degrees
	static Angle degrees(float deg){
		return Angle(deg*pi()/180.f);
	}

	/// @brief create a new Angle using radians
	static Angle radians(float rad){
		return Angle(rad);
	}

	/// @brief get angle in radians
	float radians() const {
		return rad;
	}

	/// @brief get approximation of the angle in degrees.
	float degrees() const {
		return rad*180/pi();
	}
private:
	Angle(float radians):rad(radians){}
	float rad;
};

namespace axis {
enum Axis{
	x,y,z
};
}
typedef axis::Axis Axis;

} //namespace helsing


#endif // HMATH_MISC_HPP
