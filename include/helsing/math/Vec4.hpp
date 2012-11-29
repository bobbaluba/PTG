/**
 * @file Vec4.hpp
 * @date 24. okt. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef VEC4_HPP
#define VEC4_HPP

#include <helsing/hmath.hpp>
#include <array>
#include <cassert>
#include <ostream>

namespace helsing {

/** @brief 3D vector using homogeneous coordinates
 * @ingroup math
 * Designed to be easy to use with OpenGL
 */
class Vec4 {
public:
	explicit Vec4(float x, float y, float z, float w):x(x),y(y),z(z),w(w){}
	explicit Vec4(float x, float y, float z):x(x),y(y),z(z),w(1){}
	explicit Vec4(float* v){std::copy(v,v+4, this->cArray);}
	const Vec4 operator -(const Vec4& rhs) const {
		return Vec4(x-rhs.x,y-rhs.y,z-rhs.z,w-rhs.w);
	}
	const Vec4 operator +(const Vec4& rhs) const {
		return Vec4(x+rhs.x,y+rhs.y,z+rhs.z,w+rhs.w);
	}
	Vec4& operator +=(const Vec4& rhs) {
		x+=rhs.x;
		y+=rhs.y;
		z+=rhs.z;
		w+=rhs.w;
		return *this;
	}
	const Vec4 operator -() const {
		return Vec4(-x,-y,-z,-w);
	}
	float& operator[](uint8_t index) {
		return array[index];
	}
	float operator *(const Vec4& rhs) const {
		return dot(rhs);
	}
	const Vec4 operator ^(const Vec4& rhs) const {
		return cross(rhs);
	}
	union {
		std::array<float, 4> array;
		float cArray[4];
		struct {
			float x,y,z,w;
		};
	};

	const Vec4 normalize() const {
		float lensqr = x*x + y*y + z*z + w*w;
		float len = std::sqrt(lensqr);
		return Vec4(x/len, y/len, z/len, w/len);
	}

	const Vec4 cross(const Vec4& rhs) const {
		const Vec4& lhs = *this;
		float v[4];
		v[0]=lhs.y*rhs.z - lhs.z*rhs.y;
		v[1]=-lhs.x*rhs.z + lhs.z*rhs.x;
		v[2]=lhs.x*rhs.y - lhs.y*rhs.x;
		v[3]=0;
		return Vec4(v);
	}

	float dot(const Vec4& rhs) const {
		return x*rhs.x+y*rhs.y+z*rhs.z; //w?
	}
	static Vec4 vector(float x, float y, float z){
		return Vec4(x,y,z,0);
	}
	///returns a point a the origin
	static Vec4 origin(){
		return Vec4(0,0,0,1);
	}
	///returns the zero vector
	static Vec4 zero(){
		return Vec4(0,0,0,0);
	}
	///returns the specified vector
	static Vec4 axis(Axis a){
		switch(a){
		case axis::x:
			return Vec4(1,0,0,0);
		case axis::y:
			return Vec4(0,1,0,0);
		case axis::z:
			return Vec4(0,0,1,0);
		default:
			assert(false);
			return zero();
		}
	}
};

inline std::ostream& operator<< (std::ostream &out, const Vec4& v){
	out << "{\t" << v.x << "\t" << v.y << "\t" << v.z << "\t" << v.w << "\t}";
	return out;
}

inline Vec4 operator * (const float lhs, const Vec4& rhs){
	Vec4 result(rhs.x*lhs, rhs.y*lhs, rhs.z*lhs, rhs.w*lhs);
	return result;
}

inline Vec4 operator * (const Vec4& lhs, const float rhs){
	return rhs * lhs;
}

} /* namespace helsing */
#endif /* VEC4_HPP */
