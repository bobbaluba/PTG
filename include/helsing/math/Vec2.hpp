/**
 * @file Vec2.hpp
 * @date 22. okt. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef VEC2_HPP
#define VEC2_HPP

#include <array>

namespace helsing{

/** @brief A 2D vector using non-homogeneous coordinates
 * @ingroup math
 */
class Vec2 {
public:
	explicit Vec2(float x, float y):x(x),y(y){}
	explicit Vec2():Vec2(0,0){}
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

#endif /* VEC2_HPP */
