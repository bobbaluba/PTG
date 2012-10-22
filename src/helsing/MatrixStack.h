/*
 * MatrixStack.h
 *
 *  Created on: 11. sep. 2012
 *      Author: johan
 */

#ifndef MATRIXSTACK_H_
#define MATRIXSTACK_H_

#include "hmath.h"

#include <vector>

namespace helsing {

class MatrixStack {
public:
	MatrixStack():
		matrices({Mat4::identity()}),
		top(&matrices.back()){
	}
	virtual ~MatrixStack();
	void pushMatrix(){
		matrices.push_back(*top);
		top = &matrices.back();
	}
	const Mat4 popMatrix(){
		const Mat4 popped = matrices.back();
		matrices.pop_back();
		top = &matrices.back();
		return popped;
	}
	void multMatrix(const Mat4& matrix){
		*top = *top * matrix;
	}
	void loadMatrix(const Mat4& matrix){
		*top = matrix;
	}
	void loadIdentity(){
		*top = Mat4::identity();
	}
	const Mat4& getMatrix(){
		return *top;
	}
	void translate(float dx, float dy, float dz){
		*top = top->translate(dx,dy,dz);
	}
	void scale(float x, float y, float z){
		*top = top->scale(x,y,z);
	}
	void rotate(const Vec4& axis, Angle angle){
		*top = top->rotate(axis, angle);
	}
private:
	std::vector<Mat4> matrices;
	Mat4 * top;
};

} /* namespace helsing */
#endif /* MATRIXSTACK_H_ */
