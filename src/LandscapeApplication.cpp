/*
 * LandscapeApplication.cpp
 *
 *  Created on: 25. sep. 2012
 *      Author: johan
 */

#include "LandscapeApplication.h"
#include "HeightMapActor.h"
#include "QuadTree.h"

using namespace helsing;

namespace ptg {

LandscapeApplication::LandscapeApplication(const ApplicationSettings& settings) :
		Application(settings),
		worldView(NULL),
		flymode(false),
		heightMapSize(65){
}

void LandscapeApplication::onInit(){
	worldView = new Renderer(window->getSize().x, window->getSize().y);
	worldView->getCamera().setPosition(Vec4(heightMapSize,heightMapSize,heightMapSize));
	worldView->getCamera().lookAt(Vec4::origin());
}

bool LandscapeApplication::handleEvent(const sf::Event& event){
	switch(event.type){
	case sf::Event::MouseButtonPressed:
		switch(event.mouseButton.button){
		case sf::Mouse::Left:
			flymode=!flymode;
			window->setMouseCursorVisible(!flymode);
			return true;
		case sf::Mouse::Right:{
			auto heightMap = new HeightMap(heightMapSize);
			//QuadTree quad(rand());
			//quad.fillHeightMap(heightMap, heightMapSize, 0, 0);
			HeightMapActor * heightMapActor = new HeightMapActor(heightMap);
			worldView->setTerrain(heightMapActor);
		}
			return true;
		default:
			return false;
		}
		break;
	default:
		return false;
	}
	return false;
}

void LandscapeApplication::onRender(){
	Camera& camera = worldView->getCamera();

	const float speed = 0.5f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		camera.forward(speed);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		camera.forward(-speed);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		camera.right(-speed);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		camera.right(speed);
	}


	if(flymode){
		const sf::Vector2i mid = sf::Vector2i(window->getSize().x/2, window->getSize().y/2)+window->getPosition();
		int dx = sf::Mouse::getPosition().x-mid.x, dy = sf::Mouse::getPosition().y-mid.y;
		sf::Mouse::setPosition(mid);
		const float mouseSensitivity = 0.002f;
		camera.pitch(Angle::radians(-mouseSensitivity * dy));
		camera.yaw(Angle::radians(-mouseSensitivity * dx));
	} else {
		camera.lookAt(Vec4::origin());
	}

	window->setActive();
	worldView->draw();
	window->display();
}

} //namespace ptg
