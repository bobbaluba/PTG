/*
 * hmath.h
 *
 *  Created on: 6. sep. 2012
 *      Author: Johan Helsing
 *
 * Math component of the helsing library
 *
 */

#ifndef HMATH_H_
#define HMATH_H_

#include "Vec2.h"

#include <initializer_list>
#include <cassert>
#include <array>
#include <cmath>
#include <ostream>

#include <GL/gl.h>
#include <GL/glu.h>

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

class Vec4 {
public:
	Vec4(float x, float y, float z, float w):x(x),y(y),z(z),w(w){}
	Vec4(float x, float y, float z):x(x),y(y),z(z),w(1){}
	Vec4(float* v){std::copy(v,v+4, this->cArray);}
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

class Mat4 {
public:
	Mat4(){
		for(uint32_t i=0; i<16; i++){
			array[i]=0;
		}
	}
	Mat4(const float data[16]){
		std::copy(data,data+16, this->cArray);
	}
	const Vec4 operator *(const Vec4& rhs) const {
		return dot(rhs);
	}
	const Mat4 operator *(const Mat4& rhs) const {
		return dot(rhs);
	}
	union{
		Vec4 column[4];
		std::array<float, 16> array;
		float cArray[16];
		float colMajor[4][4];
	};
	const Mat4 dot(Mat4 rhs) const {
		const Mat4& lhs = *this;
		Mat4 result;
		for(uint8_t i=0; i<4; i++){
			//ith row
			for(uint8_t j=0; j<4; j++){
				//jth column
				float cell = 0;
				for(uint8_t k=0; k<4; k++){
					cell+=lhs.column[k].array[i]*rhs.column[j].array[k];
				}
				result.column[j][i] = cell;
			}
		}
		return result;
	}
	const Vec4 dot(Vec4 rhs) const {
		const Mat4& lhs = *this;
		Vec4 result = Vec4::zero();
		for(uint8_t i=0; i<4; i++){
			//ith row
			float cell = 0;
			for(uint8_t j=0; j<4; j++){
				//jth column
				cell+=lhs.colMajor[j][i]*rhs[j];
			}
			result[i] = cell;
		}
		return result;
	}

	const Mat4 transpose() const {
		Mat4 result(true);
		for(int i = 0; i<16; i++){
			result.array[i]=array[i*4+(i%4)/4];
		}
		return result;
	}
	const Mat4 rotate(Axis axis, Angle angle) const {
		const Mat4 rotated = *this * rotation(axis, angle);
		return rotated;
	}
	const Mat4 rotate(const Vec4& axis, Angle angle) const {
		const Mat4 rotated = *this * rotation(axis, angle);
		return rotated;
	}
	const Mat4 translate(float dx, float dy, float dz) const {
		const Mat4 translated = *this * translation(dx, dy, dz);
		return translated;
	}
	const Mat4 scale(float x, float y, float z){
		const Mat4 scaled = *this * scaling(x,y,z);
		return scaled;
	}
	static const Mat4 rotation(Axis axis, Angle angle){
		float radians = angle.radians();
		Mat4 rotation = identity();
		uint8_t firstRow, secondRow, firstColumn, secondColumn;
		switch(axis){
		case axis::x:
			firstRow=1; secondRow=2; firstColumn=1; secondColumn=2;
			break;
		case axis::y:
			firstRow=2; secondRow=0; firstColumn=2; secondColumn=0;
			break;
		case axis::z:
			firstRow=0; secondRow=1; firstColumn=0; secondColumn=1;
			break;
		}
		rotation.column[firstColumn][firstRow] = std::cos(radians);
		rotation.column[firstColumn][secondRow] = std::sin(radians);
		rotation.column[secondColumn][firstRow] = -std::sin(radians);
		rotation.column[secondColumn][secondRow] = std::cos(radians);
		return rotation;
	}
	static const Mat4 rotation(Vec4 axis, Angle angle){
		float degrees = angle.degrees();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		float m[16];
		glRotatef(degrees, axis.x, axis.y, axis.z);
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glPopMatrix();
		const Mat4 rotation(m);
		return rotation;
	}
	static const Mat4 identity(){
		const float i[16] = {
			1.f,0.f,0.f,0.f,
			0.f,1.f,0.f,0.f,
			0.f,0.f,1.f,0.f,
			0.f,0.f,0.f,1.f
		};
		return Mat4(i);
	}
	static const Mat4 translation(float dx, float dy, float dz){
		const float i[16] = {
			1.f,0.f,0.f,0,
			0.f,1.f,0.f,0,
			0.f,0.f,1.f,0,
			dx,dy,dz,1.f
		};
		return Mat4(i);
	}
	static const Mat4 scaling(float dx, float dy, float dz){
		const float i[16] = {
			 dx,0.f,0.f,0.f,
			0.f, dy,0.f,0.f,
			0.f,0.f, dz,0.f,
			0.f,0.f,0.f,1.f
		};
		return Mat4(i);
	}

	static const Mat4 perspective(Angle fov, float width, float height, float near, float far){
		glMatrixMode (GL_MODELVIEW); //set the matrix to projection
		glPushMatrix();
		glLoadIdentity();
		gluPerspective(fov.degrees(), (GLfloat)width / (GLfloat)height, near, far);
		float m[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glLoadIdentity();
		glPopMatrix();
		return Mat4(m);
	}
private:
	Mat4(bool noInit){}
};

inline std::ostream& operator<< (std::ostream &out, const Mat4& m){
	//TODO restore these after
	out.setf(std::ios::fixed);
	out.setf(std::ios::showpoint);
	out.precision(2); //to limit to 2 decimal places

	out << "Matrix: \n";
	for(uint8_t i=0; i<4; i++){
		for(uint8_t j=0; j<4; j++){
			out << m.column[j].array[i] << '\t';
		}
		out << '\n';
	}
	out << '\n';
	return out;
}

}

#endif /* HMATH_H_ */
