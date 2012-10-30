#include <helsing/hmath.h>

#include <iostream>
#include <cassert>
#include <cmath>

namespace {

using std::cout;
using namespace helsing;

inline void assertf(float a, float b, float limit){
	assert(std::abs(a-b) < limit);
}

inline void assertf(float a, float b){
	assert(std::abs(a-b) < 0.001f);
}

void angles(){
	cout << "Testing angles...";
	const Angle a = Angle::radians(pi());
	assert(std::abs(a.radians() - pi()) < 0.001f);
	assert(std::abs(a.degrees() - 180) < 0.001f);

	const Angle b = Angle::degrees(180);
	assert(std::abs(b.radians() - pi()) < 0.001f);
	assert(std::abs(b.degrees() - 180) < 0.001f);
	cout << "OK!\n";
}

void identity(){
	cout << "Testing identity...";
	const Mat4 identity = Mat4::identity();
	const Vec4 a = Vec4::vector(1,2,3);
	const Vec4 ia = identity.dot(a);
//	cout << "Identity: " << identity << std::endl;
//	cout << "a: " << a << std::endl;
//	cout << "ia: " << ia << std::endl;
	assert(a.x == ia.x && a.y == ia.y && a.z == ia.z && a.w == ia.w);
	cout << "OK!\n";
}

void rotationAxes(){
	cout << "Testing vector rotation about coordinate axes...";
	{
		const Mat4 rot = Mat4::rotation(Axis::z, Angle::degrees(90));
		const Vec4 y = rot.dot(Vec4::axis(Axis::x));
		assert(almostEqual(y.x, 0, 0.001));
		assert(almostEqual(y.y, 1, 0.001));
		assert(almostEqual(y.z, 0, 0.001));
	}
	{
		const Mat4 rot = Mat4::rotation(Axis::x, Angle::degrees(90));
		const Vec4 z = rot.dot(Vec4::axis(Axis::y));
		assert(almostEqual(z.x, 0, 0.001));
		assert(almostEqual(z.y, 0, 0.001));
		assert(almostEqual(z.z, 1, 0.001));
	}
	{
		const Mat4 rot = Mat4::rotation(Axis::y, Angle::degrees(90));
		const Vec4 x = rot.dot(Vec4::axis(Axis::z));
		assert(almostEqual(x.x, 1, 0.001));
		assert(almostEqual(x.y, 0, 0.001));
		assert(almostEqual(x.z, 0, 0.001));
	}
	cout << "OK!\n";
}

void rotationArbitrary(){
	cout << "Testing vector rotation about arbitrary axes...";
	{
		//rotation about an "arbitrary" axis
		const Mat4 rot = Mat4::rotation(Vec4::axis(Axis::y), Angle::degrees(90));
		const Vec4 x = rot*Vec4::axis(Axis::z);
		assert(almostEqual(x.x, 1, 0.001));
		assert(almostEqual(x.y, 0, 0.001));
		assert(almostEqual(x.z, 0, 0.001));
	}
	cout << "OK!\n";
}

}

int main(){
	cout.setf(std::ios::fixed);
	cout.setf(std::ios::showpoint);
	cout.precision(2); //to limit to 2 decimal places
	//test the stuffs
	cout << "Testing math lib\n\n";
	angles();
	identity();
	rotationAxes();
	rotationArbitrary();
	cout << "\nAll tests completed\n";
}
