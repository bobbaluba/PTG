/**
 * @file Camera.hpp
 * @date 6. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <helsing/hmath.hpp>

namespace helsing {

class Camera {
public:
	explicit Camera():position(Vec4::origin()), matrix(Mat4::identity()){
	}
	void lookAt(const Vec4& target, const Vec4& up = Vec4::vector(0,1,0)){
		Vec4 n = (position-target).normalize();
		Vec4 u = up.cross(n);
		Vec4 v = n.cross(u);

		float * m = matrix.cArray;
		m[0]=u.x; m[4]=u.y; m[8]=u.z;
		m[1]=v.x; m[5]=v.y; m[9]=v.z;
		m[2]=n.x; m[6]=n.y; m[10]=n.z;

		setPosition(position);
	}
	void setPosition(const Vec4& pos){
		position = pos;
		const Vec4 eyeVector = position - Vec4::origin();
		matrix.cArray[12] = -eyeVector * getU();
		matrix.cArray[13] = -eyeVector * getV();
		matrix.cArray[14] = -eyeVector * getN();
	}
	void move(Vec4 distance){
		setPosition(position+distance);
	}
	void forward(float distance){
		setPosition(position - distance * getN());
	}
	void right(float distance){
		setPosition(position + distance * getU());
	}
	void up(float distance){
		setPosition(position + distance * getV());
	}
	void setOrientation(const Vec4& u, const Vec4& v, const Vec4& n){
		float * m = matrix.cArray;
		m[0]=u.x; m[4]=u.y; m[8]=u.z;
		m[1]=v.x; m[5]=v.y; m[9]=v.z;
		m[2]=n.x; m[6]=n.y; m[10]=n.z;
	}
	void transformNormals(const Mat4& transformation){
		const Vec4 u = transformation * getU();
		const Vec4 v = transformation * getV();
		const Vec4 n = transformation * getN();
		setOrientation(u,v,n);
		setPosition(position);
	}
	void pitch(Angle angle){
		const Mat4 rotation = Mat4::rotation(getU().normalize(), angle);
		transformNormals(rotation);
	}
	void yaw(Angle angle){
		const Mat4 rotation = Mat4::rotation(Axis::y, angle);
		transformNormals(rotation);
	}
	void roll(Angle angle){
		matrix = Mat4::rotation(Axis::z, angle) * matrix;
	}
	const Mat4 getMatrix() const {
		return matrix;
	}

	Vec4 getPosition() const {
		return position;
	}

	Camera(const Camera&) = default;
	Camera & operator=(const Camera&) = default;
private:
	Vec4 getU() const {
		const float * m = matrix.cArray;
		return Vec4(m[0],m[4],m[8],0);
	}
	Vec4 getV() const {
		const float * m = matrix.cArray;
		return Vec4(m[1],m[5],m[9],0);
	}
	Vec4 getN() const {
		const float * m = matrix.cArray;
		return Vec4(m[2],m[6],m[10],0);
	}

	//members
	Vec4 position;
	Mat4 matrix;
};

}

#endif /* CAMERA_HPP */
