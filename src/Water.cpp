/*
 * Water.cpp
 *
 *  Created on: 15. sep. 2012
 *      Author: johan
 */

#include "Water.h"
#include "GL/gl.h"

void Water::draw(){
	float half = size/2.f;
	glPushMatrix();
	//glTranslatef(-size/2, 0, -size/2);
	glBegin(GL_QUADS);
	glColor3f(0.1,0.2,0.8);
	glNormal3f(0,1,0);
	glVertex3f(-half,0,half);
	glVertex3f(half,0,half);
	glVertex3f(half,0,-half);
	glVertex3f(-half,0,-half);
	glEnd();
	glPopMatrix();
}
