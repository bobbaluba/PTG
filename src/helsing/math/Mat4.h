/*
 * Mat4.h
 *
 *  Created on: 24. okt. 2012
 *      Author: johan
 */

#ifndef MAT4_H_
#define MAT4_H_

#include "hmath_misc.h"
#include "Vec4.h"
#include <GL/gl.h>
#include <GL/glu.h>

namespace helsing {

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
	/** Generates a rotation matrix about an arbitrary axis
	 * @return Rotation matrix
	 */
	static const Mat4 rotation(Vec4 axis, Angle angle){
		//This implementation is based on the method described here:
		//http://science.kennesaw.edu/~plaval/math4490/rotgen.pdf
		const float radians = angle.radians();
		const float c = cos(radians);
		const float s = sin(radians);
		const float t = 1 - c;
		const Vec4& u = axis; //to make shorter expressions that more closely resembles the proof in the pdf mentioned above

		float m[16];
		m[0] = t*u.x*u.x + c;     m[4] = t*u.x*u.y - s*u.z; m[8] = t*u.x*u.z + s*u.y; m[12] = 0;
		m[1] = t*u.x*u.y + s*u.z; m[5] = t*u.y*u.y + c;     m[9] = t*u.y*u.z - s*u.x; m[13] = 0;
		m[2] = t*u.x*u.z - s*u.y; m[6] = t*u.y*u.z + s*u.x; m[10] = t*u.z*u.z + c;    m[14] = 0;
		m[3] = 0;                 m[7] = 0;                 m[11] = 0;                m[15] = 1;

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

} /* namespace helsing */
#endif /* MAT4_H_ */
