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
	width = heightMap.getSize();

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
//	TerrainVertex a = {helsing::Vec4(-0.5, 0.0, 0.0, 1),helsing::Vec4(0,0,1,0)};
//	TerrainVertex b = {helsing::Vec4( 0.5, 0.0, 0.0, 1),helsing::Vec4(0,0,1,0)};
//	TerrainVertex c = {helsing::Vec4( 0.0, 0.5, 0.0, 1),helsing::Vec4(0,0,1,0)};
//	vertices.push_back(a);
//	vertices.push_back(b);
//	vertices.push_back(c);

	//debug stuff
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(TerrainVertex)*vertices.size(), &(vertices[0]), GL_STATIC_DRAW); //offsetof?
	GLint positionAttributeIndex = shader->getPositionAttributeIndex();
	if(positionAttributeIndex==-1){
		std::cerr << "Error: Can't find attribute index for the position\n";
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
		std::cerr << "Error: Can't find attribute index for the normal\n";
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
	using helsing::Mat4;
	float midpoint = (width-1)/2.0;
	float s = 65.0/(width-1.0);
	Mat4 mv = modelViewMatrix;
	mv = mv.scale(s,s,s);
	mv = mv.translate(-midpoint,0,-midpoint);

	shader->use(mv, projectionMatrix);
	glBindVertexArray(vaoId);
	glDrawArrays(
			GL_TRIANGLES,    //which primitive to draw
			0,
			numberOfVertices //number of times the vertex shader will run
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
