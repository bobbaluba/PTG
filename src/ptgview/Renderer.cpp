/**
 * @file Renderer.cpp
 * @date 2012
 * @author Johan Klokkhammer Helsing
 */
#include "Renderer.hpp"
#include "Water.hpp"

#include <SFML/OpenGL.hpp>
#include <GL/glu.h>

#include <cmath>
#include <iostream>
#include <cassert>

using namespace helsing;
using namespace std;

const Vec4 light_position = { 2.0, 1.0, 0.0, 0.0 };

Renderer::Renderer(uint32_t width, uint32_t height) :
		width(width),
		height(height),
		water(65),
		waterLevel(0),
		terrainMesh(NULL){
	resize(width,height);
	setGLStates();
}

Renderer::~Renderer(){
}

void Renderer::setHeightMap(helsing::HeightMap* heightMap) {
	this->terrainMesh = new TerrainMesh(*heightMap); //TODO delete
}

void Renderer::setGLStates(){
	GLfloat light1_ambient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat light1_diffuse[] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position.cArray);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);

	//enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Renderer::resize(uint32_t width, uint32_t height){
	this->height = height;
	this->width = width;
	float aspectRatio = float(width)/float(height);
	glViewport(0, 0, width, height);
	const helsing::Angle fov = helsing::Angle::degrees(60);
	projection.loadMatrix(helsing::Mat4::perspective(fov, aspectRatio,0.1f,1000.f));
}

void Renderer::draw(){
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glLightfv(GL_LIGHT1, GL_POSITION, light_position.cArray); //TODO remove

	modelView.pushMatrix();

	//set up camera
	helsing::Mat4 cameraTransformation = camera.getMatrix();
	modelView.loadMatrix(cameraTransformation);


	if(terrainMesh!=NULL){
		terrainMesh->draw(modelView.getMatrix(), projection.getMatrix());
	}

	modelView.pushMatrix();
	modelView.translate(0,waterLevel,0);
	water.draw(modelView.getMatrix(), projection.getMatrix());
	modelView.popMatrix(); //water

	modelView.popMatrix(); //camera

	GLenum error = glGetError();
	while(error!=GL_NO_ERROR){
		std::cerr << "\nOpenGL error occured: " << gluErrorString(error) << "\n";
		error = glGetError();
	}
}
