/**
 * @file TerrainMesh.cpp
 * @date 2. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#include "TerrainMesh.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>
#include <helsing/TextFile.hpp>

TerrainMesh::TerrainMesh(const helsing::HeightMap& heightMap):numberOfVertices(0) {
	helsing::TextFile vertexFile("data/shaders/terrain.vert.glsl");
	helsing::TextFile fragmentFile("data/shaders/terrain.frag.glsl");
	shader = new helsing::Shader(vertexFile.str(), fragmentFile.str());

	//create vertices
	unsigned int size = heightMap.getSize();
	std::vector<TerrainVertex> vertices;
	vertices.reserve(size*size);
	for(unsigned int i=0; i<size-1; i++){
		for(unsigned int j=0; j<size-1; j++){
			//top triangle
			vertices.push_back(getVertex(i  ,j  ,heightMap));
			vertices.push_back(getVertex(i+1,j+1,heightMap));
			vertices.push_back(getVertex(i+1,j   ,heightMap));

			//bottom triangle
			vertices.push_back(getVertex(i  ,j  ,heightMap));
			vertices.push_back(getVertex(i  ,j+1,heightMap));
			vertices.push_back(getVertex(i+1,j+1,heightMap));
		}
	}
	numberOfVertices = vertices.size();

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
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(TerrainVertex), &(vertices[0]), GL_STATIC_DRAW); //offsetof?
	GLint positionAttributeIndex = shader->getPositionAttributeIndex();
	glVertexAttribPointer(
		positionAttributeIndex, //attribute index
		4,                      //size
		GL_FLOAT,               //type
		GL_FALSE,               //normalize?
		sizeof(TerrainVertex),  //stride
		0                       //array buffer offset
	);
	GLint normalAttributeIndex = shader->getNormalAttributeIndex();
	glVertexAttribPointer(
		normalAttributeIndex,  //attribute index
		4,                     //size
		GL_FLOAT,              //type
		GL_FALSE,              //normalize?
		sizeof(TerrainVertex), //stride
		(GLvoid*)sizeof(helsing::Vec4)  //array buffer offset
	);
	glEnableVertexAttribArray(0);

	//clean up
	glBindVertexArray(0); // disable vertex array object
}

TerrainMesh::~TerrainMesh() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vaoId);

	delete shader;
}

void TerrainMesh::draw(const helsing::Mat4& modelViewMatrix, const helsing::Mat4& projectionMatrix) {
	shader->use(modelViewMatrix, projectionMatrix);
	glBindVertexArray(vaoId);
	glDrawArrays(
			GL_TRIANGLES,    //which primitive to draw
			0,
			numberOfVertices //number of times the vertex shader will run
	);
	glBindVertexArray(0); //disable vertex array object
}

TerrainMesh::TerrainVertex TerrainMesh::getVertex(int x, int z, const helsing::HeightMap&) {
	using helsing::Vec4;
	Vec4 position = Vec4(x,0,z);
	Vec4 normal = Vec4::axis(helsing::axis::y);
	TerrainVertex vertex = {position,normal};
	return vertex;
}
