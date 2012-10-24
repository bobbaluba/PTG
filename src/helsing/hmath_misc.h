/*
 * hmath_misc.h
 *
 *  Created on: 24. okt. 2012
 *      Author: johan
 */

#ifndef HMATH_MISC_H_
#define HMATH_MISC_H_

#include <cmath>

namespace helsing {

//TODO switch to constexpr!!
inline double pi() { return std::atan(1)*4; }

// Usable AlmostEqual function
inline bool almostEqual(float a, float b, float epsilon){
	return std::abs(a-b) < epsilon;
}

inline float smoothStep(float t){
	return t * t * (3 - 2 * t);
}

class Angle {
public:
	static Angle degrees(float deg){
		return Angle(deg*pi()/180.f);
	}
	static Angle radians(float rad){
		return Angle(rad);
	}
	float radians() const {
		return rad;
	}
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


#endif /* HMATH_MISC_H_ */
