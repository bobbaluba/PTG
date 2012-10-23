#include "Renderer.h"
#include "quad.h"
#include "Water.h"

#include <SFML/OpenGL.hpp>

#include <cmath>
#include <iostream>
#include <cassert>

using namespace helsing;
using namespace ptg;
using namespace std;

const Vec4 light_position = { 2.0, 1.0, 0.0, 0.0 };

Renderer::Renderer(uint32_t width, uint32_t height) :
		width(width),
		height(height),
		waterActor(64),
		landscapeActor(NULL){
	resize(width,height);
	setGLStates();
}

Renderer::~Renderer(){
}

void Renderer::setGLStates(){
	GLfloat light1_ambient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat light1_diffuse[] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position.cArray);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
//
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Renderer::resize(uint32_t width, uint32_t height){
	this->height = height;
	this->width = width;
	glViewport(0, 0, width, height);
	const helsing::Angle fov = helsing::Angle::degrees(60);
	projection.loadMatrix(helsing::Mat4::perspective(fov, width,height,0.1f,1000.f));

	//TODO remove
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(projection.getMatrix().cArray);
}

void Renderer::draw(){

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//set up camera
	glLoadIdentity();
	helsing::Mat4 cameratransformation = camera.getMatrix();
	glLightfv(GL_LIGHT1, GL_POSITION, (modelView.getMatrix()*light_position).cArray);
	glLoadMatrixf(cameratransformation.cArray);

	//draw stuff
	if(landscapeActor)landscapeActor->draw();
	waterActor.draw();

	glPopMatrix();

	GLenum error = glGetError();
	if(error!=GL_NO_ERROR){
		std::cerr << "There is an error!\n";
	}
}

void Renderer::drawVector(const helsing::Vec4& position, const helsing::Vec4& vector){
	glBegin(GL_LINES); //blæææ
	glColor3f(1,1,1);
	glVertex3fv(position.cArray);
	glVertex3fv((position+vector).cArray);
	glEnd();
}

void Renderer::drawHeightMap(const HeightMap& heightMap) {
	auto size = heightMap.getSize();
	glPushMatrix();
	glTranslatef(-32, 0, -32);
	//	glScalef(1.f/(size-1), 1, 1.f/(size-1));
	for (uint32_t i = 0; i < size - 1; i++) {
		glColor3f(0.2, 0.8, 0.3);
		glBegin(GL_TRIANGLE_STRIP);
		for (uint32_t j = 0; j < size - 1; j++) {
			//gfx::drawVector(getPoint(i+1,j), getNormal(i+1,j));

			glNormal3fv(heightMap.getNormal(i + 1, j).cArray);
			//			glColor3f(getHeight(i+1, j)*2,.2,.2);
			glVertex3f(i + 1, heightMap.getHeight(i + 1, j), j);

			glNormal3fv(heightMap.getNormal(i, j).cArray);
			//			glColor3f(getHeight(i,j)*2,.2,.2);
			glVertex3f(i, heightMap.getHeight(i, j), j);

			glNormal3fv(heightMap.getNormal(i + 1, j + 1).cArray);
			//			glColor3f(getHeight(i+1, j+1)*2,.2,.2);
			glVertex3f(i + 1, heightMap.getHeight(i + 1, j + 1), j + 1);

			glNormal3fv(heightMap.getNormal(i, j + 1).cArray);
			//			glColor3f(getHeight(i, j+1)*2,.2,.2);
			glVertex3f(i, heightMap.getHeight(i, j + 1), j + 1);

		}
		glEnd();
	}

	//draw normals
	//	for(uint32_t i = 0; i<size; i++){
	//		for(uint32_t j=0; j<size; j++){
	//			drawVector(getPoint(i,j), getNormal(i,j));
	//		}
	//	}
	glPopMatrix();
}
