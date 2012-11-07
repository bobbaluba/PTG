/**
 * @file Water.cpp
 * @date 15. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#include "Water.hpp"
#include "GL/gl.h"

void Water::draw(const helsing::Mat4& modelViewMatrix, const helsing::Mat4& projectionMatrix){
	glDisable(GL_LIGHTING);

	//load the projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadMatrixf(projectionMatrix.cArray);

	//load the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(modelViewMatrix.cArray);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);

	float half = size/2.f;
	glColor4f(0.1,0.2,0.8,0.2);
	for(int i=-5; i<0; i++){
		glVertex3f(-half,i,half);
		glVertex3f(half,i,half);
		glVertex3f(half,i,-half);
		glVertex3f(-half,i,-half);
	}

	glColor4f(0.1,0.2,0.8,0.7);
	glVertex3f(-half,0,half);
	glVertex3f(half,0,half);
	glVertex3f(half,0,-half);
	glVertex3f(-half,0,-half);
	glEnd();

	glPopMatrix(); //modelview matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); //restore original projection matrix
}
