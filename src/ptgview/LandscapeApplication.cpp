/**
 * @file LandscapeApplication.cpp
 * @date 25. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#include "LandscapeApplication.hpp"
#include "HeightMapActor.hpp"

#include <ptg/MidpointDisplacementTerrain.hpp>
#include <ptg/DiamondSquareTerrain.hpp>

#include <iostream>

using namespace helsing;

LandscapeApplication::LandscapeApplication(const ApplicationSettings& settings) :
		Application(settings),
		renderer(NULL),
		flymode(false),
		heightMapSize(9),
		terrain(&diamondSquareTerrain),
		amplitude(0.6),
		gain(0.5),
		waterLevel(0)
{
	continuous2DSignalTerrain.setSignal(&perlinNoise);
}

void LandscapeApplication::onInit(){
	renderer = new Renderer(window->getSize().x, window->getSize().y);
	renderer->getCamera().setPosition(Vec4(30,5,30));
	renderer->getCamera().lookAt(Vec4::origin());
	updateHeightMap();
}

bool LandscapeApplication::handleEvent(const sf::Event& event) {
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		switch (event.mouseButton.button) {
		case sf::Mouse::Left:
			flymode = !flymode;
			window->setMouseCursorVisible(!flymode);
			return true;
		case sf::Mouse::Right: {
			unsigned int seed = rand();
			std::cout << "Reseeding terrain with seed: " << seed << std::endl;
			terrain->seed(seed);
			updateHeightMap();
		}
			return true;
		default:
			return false;
		} // end mouse button switch
		break;
	case sf::Event::KeyPressed:
		switch(event.key.code){
		case sf::Keyboard::P:
			increaseDetail();
			return true;
		case sf::Keyboard::O:
			decreaseDetail();
			return true;
		case sf::Keyboard::L:
			increaseAmplitude();
			break;
		case sf::Keyboard::K:
			decreaseAmplitude();
			break;
		case sf::Keyboard::M:
			increaseGain();
			break;
		case sf::Keyboard::N:
			decreaseGain();
			break;
		case sf::Keyboard::Num1:
			std::cout << "Switching to diamond square terrain\n";
			setTerrain(&diamondSquareTerrain);
			break;
		case sf::Keyboard::Num2:
			std::cout << "Switching to midpoint displacement terrain\n";
			setTerrain(&midpointDisplacementTerrain);
			break;
		case sf::Keyboard::Num3:
			std::cout << "Switching to perlin noise terrain\n";
			continuous2DSignalTerrain.setSignal(&perlinNoise);
			setTerrain(&continuous2DSignalTerrain);
			break;
		case sf::Keyboard::Num4:
			std::cout << "Switching to fractional brownian noise terrain\n";
			continuous2DSignalTerrain.setSignal(&fractionalBrownianMotion);
			setTerrain(&continuous2DSignalTerrain);
			break;
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
	Camera& camera = renderer->getCamera();

	//camera movement
	const float speed = 0.5f; //todo scale with time
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
		camera.up(speed);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
		camera.up(-speed);
	}

	//Water levels
	const float waterSpeed=0.1f; //todo scale with time
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
		raiseWater(waterSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		raiseWater(-waterSpeed);
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
	renderer->draw();
	window->display();
}

void LandscapeApplication::setTerrain(Terrain* terrain) {
	this->terrain = terrain;
	updateHeightMap();
}

void LandscapeApplication::increaseDetail() {
	unsigned int newSize = (heightMapSize-1)*2+1;
	setHeightMapSize(newSize);
}

void LandscapeApplication::decreaseDetail() {
	unsigned int newSize = (heightMapSize)/2+1;
	if(newSize<3)newSize=3;
	setHeightMapSize(newSize);
}

void LandscapeApplication::setHeightMapSize(unsigned int size) {
	heightMapSize=size;
	updateHeightMap();
}

void LandscapeApplication::increaseAmplitude() {
	amplitude *= 1.1;
	std::cout << "Increasing amplitude to: " << amplitude << std::endl;
	midpointDisplacementTerrain.setAmplitude(amplitude);
	diamondSquareTerrain.setAmplitude(amplitude);
	continuous2DSignalTerrain.setAmplitude(amplitude);
	updateHeightMap();
}

void LandscapeApplication::decreaseAmplitude() {
	amplitude /= 1.1;
	std::cout << "Decreasing amplitude to: " << amplitude << std::endl;
	midpointDisplacementTerrain.setAmplitude(amplitude);
	diamondSquareTerrain.setAmplitude(amplitude);
	continuous2DSignalTerrain.setAmplitude(amplitude);
	updateHeightMap();
}

void LandscapeApplication::increaseGain() {
	gain*=1.05;
	std::cout << "Increasing gain to: " << gain << std::endl;
	diamondSquareTerrain.setGain(gain);
	midpointDisplacementTerrain.setGain(gain);
	updateHeightMap();
}

void LandscapeApplication::decreaseGain() {
	gain/=1.05;
	std::cout << "Decreasing gain to: " << gain << std::endl;
	diamondSquareTerrain.setGain(gain);
	midpointDisplacementTerrain.setGain(gain);
	updateHeightMap();
}

void LandscapeApplication::raiseWater(float amount) {
	waterLevel+=amount;
	renderer->setWaterLevel(waterLevel);
}

void LandscapeApplication::updateHeightMap() {
	if(terrain==NULL){
		return;
	}

	std::cout << "Generating " << heightMapSize << "x" << heightMapSize << "heightMap..."; std::flush(std::cout);
	HeightMap* heightMap = new HeightMap(heightMapSize);
	*heightMap = terrain->generateHeightMap(heightMapSize, heightMapSize);
	std::cout << "OK!\n";

	if(renderer!=NULL){
		renderer->setHeightMap(heightMap);
	}
}
