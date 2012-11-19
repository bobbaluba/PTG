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

namespace {

inline unsigned int getIndex(unsigned int i, unsigned int j, unsigned int width){
	return i+j*width;
}

}

TerrainMesh::TerrainMesh(const helsing::HeightMap& heightMap, helsing::Shader* shader):
		numberOfVertices(0),
		shader(shader)
{
	width = heightMap.getSize();

	//create vertices
	unsigned int size = heightMap.getSize();
	std::vector<TerrainVertex> vertices;
	vertices.reserve(size*size);
	for(unsigned int i=0; i<size; i++){
		for(unsigned int j=0; j<size; j++){
			vertices.push_back(getVertex(i,j,heightMap));
		}
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(TerrainVertex)*vertices.size(), &(vertices[0]), GL_STATIC_DRAW); //offsetof?
	GLint positionAttributeIndex = shader->getPositionAttributeIndex();
	if(positionAttributeIndex==-1){
		std::cerr << "\nError: Can't find attribute index for the position\n";
		exit(EXIT_FAILURE);
	}
	glVertexAttribPointer(
		positionAttributeIndex,           //attribute index
		4,                                //size
		GL_FLOAT,                         //type
		GL_FALSE,                         //normalize?
		sizeof(TerrainVertex),            //stride
		(GLvoid*)offsetof(TerrainVertex, position) //array buffer offset
	);
	glEnableVertexAttribArray(positionAttributeIndex);

	GLint normalAttributeIndex = shader->getNormalAttributeIndex();
	if(normalAttributeIndex==-1){
		std::cerr << "\nError: Can't find attribute index for the normal\n";
		exit(EXIT_FAILURE);
	}
	glVertexAttribPointer(
		normalAttributeIndex,                     //attribute index
		4,                                        //size
		GL_FLOAT,                                 //type
		GL_FALSE,                                 //normalize?
		sizeof(TerrainVertex),                    //stride
		(GLvoid*)offsetof(TerrainVertex, normal)  //array buffer offset
	);
	glEnableVertexAttribArray(normalAttributeIndex);

	//set up index array
	//TODO could this be shared across instances?
	std::vector<GLuint> indices; //TODO is this really 32-bit integers as it should be?
//	for(unsigned int i=0; i<size-1; i++){
//		for(unsigned int j=0; j<size-1; j++){
//			//top triangle
//			indices.push_back(getIndex(i,   j+1, width));
//			indices.push_back(getIndex(i,   j,   width));
//			indices.push_back(getIndex(i+1, j+1,   width));
//			//bottom triangle
//			indices.push_back(getIndex(i+1, j, width));
//		}
//		//TODO break the current triangle strip with primitive restart index
//	}
	//temporary index generation while stitching triangle strips doesn't work
	for(unsigned int row = 0; row < width - 1; row++){
		if((row % 2) == 0){ // even rows
			for(unsigned int col = 0; col < width; col++){
				indices.push_back(col + (row+1) * width);
				indices.push_back(col + row * width);
			}
		} else { // odd rows
			for (unsigned int col = width - 1; col > 0; col--){
				indices.push_back(col - 1 + row * width);
				indices.push_back(col + (row+1) * width);
			}
		}
	}

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)*indices.size(), &indices[0], GL_STATIC_DRAW);

	numberOfVertices = indices.size();

	//clean up
	glBindVertexArray(0); // disable vertex array object
}

TerrainMesh::~TerrainMesh() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vaoId);
}

void TerrainMesh::draw(const helsing::Mat4& modelViewMatrix, const helsing::Mat4& projectionMatrix) {
	using helsing::Mat4;
	float midpoint = (width-1)/2.0;
	float s = 65.0/(width-1.0);
	Mat4 mv = modelViewMatrix;
	mv = mv.scale(s,s,s);
	mv = mv.translate(-midpoint,0,-midpoint);

	shader->use(mv, projectionMatrix);
	glBindVertexArray(vaoId);
	glDrawElements(
			GL_TRIANGLE_STRIP,
			numberOfVertices,
			GL_UNSIGNED_INT,
			0 //Specifies a pointer to the location where the indices are stored.
	);
	glBindVertexArray(0); //disable vertex array object
}

TerrainMesh::TerrainVertex TerrainMesh::getVertex(int x, int z, const helsing::HeightMap& heightMap) {
	using helsing::Vec4;
	Vec4 position = Vec4(x,heightMap.getHeight(x,z),z);
	Vec4 normal = heightMap.getNormal(x,z);
	TerrainVertex vertex = {position,normal};
	return vertex;
}
