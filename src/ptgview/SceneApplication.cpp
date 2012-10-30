/*
 * SceneApplication.cpp
 *
 *  Created on: 25. sep. 2012
 *      Author: Johan Klokkhammer Helsing
 */

#include "SceneApplication.hpp"

LayoutApplication::LayoutApplication(const ApplicationSettings& settings) : Application(settings), scene(NULL){
}

LayoutApplication::~LayoutApplication() {
}

void LayoutApplication::setScene(Scene* scene){
	this->scene->hide();
	scene->show();
	this->scene=scene;
}