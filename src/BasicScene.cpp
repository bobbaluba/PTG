/*
 * BasicScene.cpp
 *
 *  Created on: 25. sep. 2012
 *      Author: johan
 */

#include "BasicScene.h"

BasicScene::BasicScene(){
}

BasicScene::~BasicScene(){
}

void BasicScene::render(){
	for(auto it = drawables.begin(); it!=drawables.end(); it++){
		(*it)->draw();
	}
}

void BasicScene::addDrawable(Drawable* drawable){
	drawables.push_back(drawable);
}
