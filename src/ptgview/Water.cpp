/**
 * @file Water.cpp
 * @date 15. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#include "Water.hpp"
#include "GL/gl.h"

void Water::draw(){
	glDisable(GL_LIGHTING);
	float half = size/2.f;
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);

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
	glPopMatrix();
}
