/**
 * @file Renderer.cpp
 * @date 2012
 * @author Johan Klokkhammer Helsing
 */
#include "Renderer.hpp"
#include "Water.hpp"

#include <helsing/TextFile.hpp>

#include <helsing/Clock.hpp>

#include <SFML/OpenGL.hpp>
#include <GL/glu.h>

#include <cmath>
#include <iostream>
#include <cassert>

using namespace helsing;
using namespace std;

Renderer::Renderer(uint32_t width, uint32_t height) :
		width(width),
		height(height),
		activeCamera(&movingCamera),
		orthogonalProjection(Mat4::orthogonal(-32,32,-32,32,-1024,1024)), //TODO remove magic numbers
		projection(&perspectiveProjection),
		water(65),
		waterLevel(0),
		terrainMesh(NULL),
		terrainShader(NULL),
		perspectiveMode(true)
		{
	resize(width,height);
	setGLStates();

	topDownCamera.setPosition(Vec4(0,65,0)); //TODO get rid of magic numbers
	topDownCamera.lookAt(Vec4::origin(), Vec4::vector(0,0,1));

	//initialize terrain shader
	helsing::TextFile vertexFile("data/shaders/terrain.vert.glsl");
	helsing::TextFile fragmentFile("data/shaders/terrain.frag.glsl");
	terrainShader = new helsing::Shader(vertexFile.str(), fragmentFile.str());
}

Renderer::~Renderer(){
	delete terrainShader;
}

void Renderer::setHeightMap(helsing::HeightMap* heightMap) {
	if(terrainMesh!=NULL){
		delete terrainMesh;
	}
	std::cout << "Creating terrain mesh...";
	std::cout.flush();
	helsing::Clock clock;
	terrainMesh = new TerrainMesh(*heightMap, terrainShader);
	std::cout << "OK! " << clock.getAsMilliseconds() <<"ms\n\n";
}

void Renderer::setPerspectiveMode(bool enabled) {
	perspectiveMode = enabled;
	//update pointer
	projection = perspectiveMode ? &perspectiveProjection : &orthogonalProjection;
}

void Renderer::setTopDownView(bool enabled) {
	topDownView = enabled;
	activeCamera = topDownView ? &topDownCamera : &movingCamera;
}

void Renderer::setGLStates(){
	//blending stuff
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	//back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Renderer::resize(uint32_t width, uint32_t height){
	this->height = height;
	this->width = width;
	float aspectRatio = float(width)/float(height);
	glViewport(0, 0, width, height);
	const helsing::Angle fov = helsing::Angle::degrees(60);
	perspectiveProjection = helsing::Mat4::perspective(fov, aspectRatio,0.1f,1000.f);
}

void Renderer::draw(){
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	modelViewStack.pushMatrix();

	//set up camera
	const Mat4 cameraTransformation = activeCamera->getMatrix();
	modelViewStack.loadMatrix(cameraTransformation);

	if(terrainMesh != NULL){
		terrainMesh->draw(modelViewStack.getMatrix(), *projection);
	}

	modelViewStack.pushMatrix();
	modelViewStack.translate(0, waterLevel, 0);
	water.draw(modelViewStack.getMatrix(), *projection);
	modelViewStack.popMatrix(); //water

	modelViewStack.popMatrix(); //camera

	GLenum error = glGetError();
	while(error!=GL_NO_ERROR){
		std::cerr << "\nOpenGL error occured: " << gluErrorString(error) << "\n";
		error = glGetError();
	}
}
