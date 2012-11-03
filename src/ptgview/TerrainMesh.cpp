/**
 * @file TerrainMesh.cpp
 * @date 2. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#include "TerrainMesh.h"

#include <GL/gl.h>
#include <iostream>
#include <vector>

TerrainMesh::TerrainMesh(const helsing::HeightMap& heightMap) {
	//create vertices
	unsigned int size = heightMap.getSize();
	std::vector<TerrainVertex> vertices;
	vertices.reserve(size*size);
	for(unsigned int i=0; i<vertices.size(); i++){
		vertices[i].position=helsing::Vec4::origin();
		vertices[i].normal=helsing::Vec4::axis(helsing::axis::y);
	}

	//Create and bind vertex array object
	glGenVertexArrays(1, &vaoId);
	if(vaoId == 0){
		std::cerr << "\nError: Couldn't allocate vertex array object\n";
		exit(EXIT_FAILURE);
	}
	glBindVertexArray(vaoId);

	//Create and bind vertex buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	//specify the data
	glBufferData(GL_ARRAY_BUFFER, size*size*sizeof(TerrainVertex), &(vertices[0]), GL_STATIC_DRAW); //offsetof?

	//clean up
	glEnableVertexAttribArray(0); // disable vertex array object
	glBindVertexArray(0); // disable vertex array object

}

TerrainMesh::~TerrainMesh() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, vboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, vaoId);
}

void TerrainMesh::draw() {
	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, 6); //TODO check manual
	glBindVertexArray(0); //disable vertex array object
}
