/**
 * @file MatrixStack.hpp
 * @date 11. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef MATRIXSTACK_HPP
#define MATRIXSTACK_HPP

#include <helsing/hmath.hpp>

#include <vector>

namespace helsing {
/** @brief A matrix stack for keeping track of current transformations
 *
 */
class MatrixStack {
public:
	explicit MatrixStack():
		matrices({Mat4::identity()}),
		top(&matrices.back()){
	}
	virtual ~MatrixStack();

	/// @brief make a copy of the current matrix and put it on the top of the stack
	void pushMatrix(){
		matrices.push_back(*top);
		top = &matrices.back();
	}

	/// @brief Pop the current matrix. Restore the matrix before pushMatrix() was called
	const Mat4 popMatrix(){
		const Mat4 popped = matrices.back();
		matrices.pop_back();
		top = &matrices.back();
		return popped;
	}

	/// @brief Multiply the current matrix.
	void multMatrix(const Mat4& matrix){
		*top = *top * matrix;
	}

	/// @brief Replace the current matrix with the given matrix.
	void loadMatrix(const Mat4& matrix){
		*top = matrix;
	}

	/// @brief Replace the current matrix with the identity matrix
	void loadIdentity(){
		*top = Mat4::identity();
	}

	/// @brief Get the matrix at the top of the stack
	const Mat4& getMatrix(){
		return *top;
	}

	/// @brief translate the current matrix
	void translate(float dx, float dy, float dz){
		*top = top->translate(dx,dy,dz);
	}

	/// @brief scale the current matrix
	void scale(float x, float y, float z){
		*top = top->scale(x,y,z);
	}

	/// @brief rotate the current matrix about the given axis
	void rotate(const Vec4& axis, Angle angle){
		*top = top->rotate(axis, angle);
	}

	MatrixStack(const MatrixStack& lhs){
		matrices = lhs.matrices;
		top = &matrices.back();
	}

	MatrixStack & operator=(const MatrixStack& lhs){
		matrices = lhs.matrices;
		top = &matrices.back();
		return *this;
	}	

private:
	std::vector<Mat4> matrices;
	Mat4 * top;
};

} // namespace helsing
#endif // MATRIXSTACK_HPP
