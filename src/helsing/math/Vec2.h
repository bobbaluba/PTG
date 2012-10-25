/*
 * Vec2.h
 *
 *  Created on: 22. okt. 2012
 *      Author: johan
 *
 * 2-Dimensional vector
 */

#ifndef VEC2_H_
#define VEC2_H_

#include <array>

namespace helsing{

class Vec2 {
public:
	Vec2(float x, float y):x(x),y(y){}
	Vec2():Vec2(0,0){}
	union {
		std::array<float, 2> array;
		float cArray[2];
		struct {
			float x,y;
		};
	};

	/// @return this - rhs
	const Vec2 subtract(const Vec2& rhs) const {
		return Vec2(x-rhs.x, y-rhs.y);
	}

	/// @return Opposite vector
	const Vec2 negate() const {
		return Vec2(-x, -y);
	}

	/// @return dot product
	float dot(const Vec2& rhs) const {
		return x*rhs.x+y*rhs.y;
	}

	/// Unary Minus
	const Vec2 operator -() const {
		return Vec2(-x,-y);
	}

	/// Binary minus
	const Vec2 operator -(const Vec2 rhs) const {
		return this->subtract(rhs);
	}

	/** Binary Multiplication
	 * 	@return dot product
	 */
	float operator *(const Vec2& rhs) const {
		return dot(rhs);
	}


};

}

#endif /* VEC2_H_ */