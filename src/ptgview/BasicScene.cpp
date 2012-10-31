/**
 * @file BasicScene.cpp
 * @date 25. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#include "BasicScene.hpp"

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
