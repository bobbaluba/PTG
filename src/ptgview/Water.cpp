/**
 * @file Water.cpp
 * @date 15. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#include "Water.hpp"

#include <helsing/TextFile.hpp>

#include <iostream>

Water::Water(float size):size(size),
		shader(
				helsing::TextFile("data/shaders/water.vert.glsl").str(),
				helsing::TextFile("data/shaders/water.frag.glsl").str()
		)
{
	//Create and bind vertex array object
	glGenVertexArrays(1, &vaoId);
	if(vaoId == 0){
		std::cerr << "\nError: Couldn't allocate vertex array object\n";
		exit(EXIT_FAILURE);
	}
	glBindVertexArray(vaoId);


	//Create and bind vertex buffer object
	GLuint vboId;
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	float vert[12] = {
			-1, 0,  1,
			 1, 0,  1,
			-1, 0, -1,
			 1, 0, -1
	};
	//specify the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*4, &vert[0], GL_STATIC_DRAW);
	GLint positionAttributeIndex = shader.getPositionAttributeIndex();
	if(positionAttributeIndex==-1){
		std::cerr << "\nError: Can't find attribute index for the position\n";
		exit(EXIT_FAILURE);
	}
	glVertexAttribPointer(
		positionAttributeIndex, //attribute index
		3,                      //size
		GL_FLOAT,               //type
		GL_FALSE,               //normalize?
		sizeof(float)*3,        //stride
		(GLvoid*)NULL           //array buffer offset
	);
	glEnableVertexAttribArray(positionAttributeIndex);

	//clean up
	glBindVertexArray(0); // disable vertex array object
}

void Water::draw(const helsing::Mat4& modelViewMatrix, const helsing::Mat4& projectionMatrix){
	float half = size/2.f;
	helsing::Mat4 mv = modelViewMatrix.scale(half,half,half);
	glBindVertexArray(vaoId);

	//draw underwater layers
	for(int i=-5; i<0; i++){
		shader.use(mv.translate(0,float(i)/20,0), projectionMatrix);
		shader.setUniform("Alpha", 0.2);
		glDrawArrays(GL_TRIANGLE_STRIP,0, 4);
	}

	//draw top layer
	shader.setUniform("Alpha", 0.7);
	shader.use(mv, projectionMatrix);
	glDrawArrays(GL_TRIANGLE_STRIP,0, 4);

	glBindVertexArray(0); //disable vertex array object


}
