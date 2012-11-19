/**
 * @file PTGView.cpp
 * @date 25. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#include "PTGView.hpp"

#include <helsing/Clock.hpp>

#include <iostream>

using namespace helsing;

PTGView::PTGView(const ApplicationSettings& settings) :
		Application(settings),
		renderer(NULL),
		flymode(false),
		heightMapSize(9),
		terrain(NULL),
		amplitude(0.6),
		gain(0.5),
		lacunarity(2),
		waterLevel(0),
		gaussianBlurTerrain(NULL),
		thermalErosionTerrain(NULL),
		blurEnabled(false),
		erosionEnabled(false)
{
	continuous2DSignalTerrain.setSignal(&perlinNoise);
}

void PTGView::onInit(){
	renderer = new Renderer(window->getSize().x, window->getSize().y);
	renderer->getCamera().setPosition(Vec4(30,5,30));
	renderer->getCamera().lookAt(Vec4::origin());
	setTerrain(&midpointDisplacementTerrain);
}

bool PTGView::handleEvent(const sf::Event& event) {
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		switch (event.mouseButton.button) {
		case sf::Mouse::Left:
			flymode = !flymode;
			window->setMouseCursorVisible(!flymode);
			return true;
		case sf::Mouse::Right:
			reseedTerrain();
			return true;
		default:
			return false;
		} // end mouse button switch
		break;
	case sf::Event::KeyPressed:
		switch(event.key.code){
		case sf::Keyboard::Return:
		case sf::Keyboard::Space:
			reseedTerrain();
			break;
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
		case sf::Keyboard::B:
			toggleBlur();
			break;
		case sf::Keyboard::E:
			toggleErosion();
			break;
		case sf::Keyboard::U:
			decreaseOctaves();
			break;
		case sf::Keyboard::I:
			increaseOctaves();
			break;
		case sf::Keyboard::Z:
			decreaseOffset();
			break;
		case sf::Keyboard::X:
			increaseOffset();
			break;
		case sf::Keyboard::C:
			decreaseLacunarity();
			break;
		case sf::Keyboard::V:
			increaseLacunarity();
			break;
		case sf::Keyboard::Q:
			togglePerspective();
			break;
		case sf::Keyboard::Tab:
			toggleTopTownView();
			break;
		case sf::Keyboard::Comma:
			decreaseH();
			break;
		case sf::Keyboard::Period:
			increaseH();
			break;
		case sf::Keyboard::F1:
			decreaseIterations();
			break;
		case sf::Keyboard::F2:
			increaseIterations();
			break;
		case sf::Keyboard::F3:
			decreaseSlope();
			break;
		case sf::Keyboard::F4:
			increaseSlope();
			break;
		case sf::Keyboard::Num1:
			std::cout << "Switching to midpoint displacement terrain\n";
			setTerrain(&midpointDisplacementTerrain);
			break;
		case sf::Keyboard::Num2:
			std::cout << "Switching to diamond square terrain\n";
			setTerrain(&diamondSquareTerrain);
			break;
		case sf::Keyboard::Num3:
			std::cout << "Switching to helsing square terrain\n";
			setTerrain(&helsingSquareTerrain);
			break;
		case sf::Keyboard::Num4:
			std::cout << "Switching to perlin noise terrain\n";
			continuous2DSignalTerrain.setSignal(&perlinNoise);
			setTerrain(&continuous2DSignalTerrain);
			break;
		case sf::Keyboard::Num5:
			std::cout << "Switching to fractional brownian perlin noise terrain\n";
			fractionalBrownianMotion.setBaseNoise(&perlinNoise);
			continuous2DSignalTerrain.setSignal(&fractionalBrownianMotion);
			setTerrain(&continuous2DSignalTerrain);
			break;
		case sf::Keyboard::Num6:
			std::cout << "Switching to value noise terrain\n";
			continuous2DSignalTerrain.setSignal(&valueNoise);
			setTerrain(&continuous2DSignalTerrain);
			break;
		case sf::Keyboard::Num7:
			std::cout << "Switching to fractional brownian value noise terrain\n";
			fractionalBrownianMotion.setBaseNoise(&valueNoise);
			continuous2DSignalTerrain.setSignal(&fractionalBrownianMotion);
			setTerrain(&continuous2DSignalTerrain);
			break;
		case sf::Keyboard::Num8:
			std::cout << "Switching to hybrid multifractal terrain with perlin noise\n";
			hybridMultiFractal.setBaseNoise(&perlinNoise);
			continuous2DSignalTerrain.setSignal(&hybridMultiFractal);
			setTerrain(&continuous2DSignalTerrain);
			break;
		case sf::Keyboard::Num9:
			std::cout << "Switching to ridged multi fractal terrain with perlin noise\n";
			ridgedMultiFractal.setBaseNoise(&perlinNoise);
			continuous2DSignalTerrain.setSignal(&ridgedMultiFractal);
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

void PTGView::onRender(){
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
		raiseWater(waterSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
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

void PTGView::setTerrain(Terrain* terrain) {
	thermalErosionTerrain.setSource(terrain);
	gaussianBlurTerrain.setSource(terrain);
	this->terrain = terrain;
	updateHeightMap();
}

void PTGView::increaseDetail() {
	unsigned int newSize = (heightMapSize-1)*2+1;
	setHeightMapSize(newSize);
}

void PTGView::decreaseDetail() {
	unsigned int newSize = (heightMapSize)/2+1;
	if(newSize<3)newSize=3;
	setHeightMapSize(newSize);
}

void PTGView::setHeightMapSize(unsigned int size) {
	heightMapSize=size;
	updateHeightMap();
}

void PTGView::increaseAmplitude() {
	amplitude *= 1.1;
	std::cout << "Increasing amplitude to: " << amplitude << std::endl;
	midpointDisplacementTerrain.setAmplitude(amplitude);
	diamondSquareTerrain.setAmplitude(amplitude);
	continuous2DSignalTerrain.setAmplitude(amplitude);
	helsingSquareTerrain.setAmplitude(amplitude);
	updateHeightMap();
}

void PTGView::decreaseAmplitude() {
	amplitude /= 1.1;
	std::cout << "Decreasing amplitude to: " << amplitude << std::endl;
	midpointDisplacementTerrain.setAmplitude(amplitude);
	diamondSquareTerrain.setAmplitude(amplitude);
	continuous2DSignalTerrain.setAmplitude(amplitude);
	helsingSquareTerrain.setAmplitude(amplitude);
	updateHeightMap();
}

void PTGView::increaseGain() {
	gain*=1.05;
	std::cout << "Increasing gain to: " << gain << std::endl;
	diamondSquareTerrain.setGain(gain);
	midpointDisplacementTerrain.setGain(gain);
	fractionalBrownianMotion.setGain(gain);
	helsingSquareTerrain.setGain(gain);
	updateHeightMap();
}

void PTGView::decreaseGain() {
	gain/=1.05;
	std::cout << "Decreasing gain to: " << gain << std::endl;
	diamondSquareTerrain.setGain(gain);
	midpointDisplacementTerrain.setGain(gain);
	fractionalBrownianMotion.setGain(gain);
	helsingSquareTerrain.setGain(gain);
	updateHeightMap();
}

void PTGView::raiseWater(float amount) {
	waterLevel+=amount;
	renderer->setWaterLevel(waterLevel);
}

void PTGView::updateHeightMap() {
	if(terrain==NULL){
		return;
	}

	std::cout << "Generating " << heightMapSize << "x" << heightMapSize << "heightMap..."; std::flush(std::cout);
	helsing::Clock clock;
	HeightMap* heightMap = new HeightMap(heightMapSize);
	if(erosionEnabled){
		*heightMap = thermalErosionTerrain.generateHeightMap(heightMapSize, heightMapSize);
	}else if(blurEnabled){
		*heightMap = gaussianBlurTerrain.generateHeightMap(heightMapSize, heightMapSize);
	} else {
		*heightMap = terrain->generateHeightMap(heightMapSize, heightMapSize);
	}
	std::cout << "OK! " << clock.getAsMilliseconds() << "ms\n";

	if(renderer!=NULL){
		renderer->setHeightMap(heightMap);
	}
}

void PTGView::reseedTerrain() {
	unsigned int seed = rand();
	std::cout << "Reseeding terrain with seed: " << seed << std::endl;
	terrain->seed(seed);
	updateHeightMap();
}

void PTGView::increaseOctaves() {
	unsigned int newValue = fractionalBrownianMotion.getOctaves() + 1;
	if(newValue>=0){
		std::cout << "Setting number of octaves to: " << newValue << "\n";
		fractionalBrownianMotion.setOctaves(newValue);
		hybridMultiFractal.setOctaves(newValue);
		ridgedMultiFractal.setOctaves(newValue);
		updateHeightMap();
	}
}

void PTGView::decreaseOctaves() {
	unsigned int oldValue = fractionalBrownianMotion.getOctaves();
	if(oldValue == 0){
		return;
	}
	unsigned int newValue = oldValue - 1;
	std::cout << "Setting number of octaves to: " << newValue << "\n";
	fractionalBrownianMotion.setOctaves(newValue);
	hybridMultiFractal.setOctaves(newValue);
	ridgedMultiFractal.setOctaves(newValue);
	updateHeightMap();
}

void PTGView::increaseLacunarity() {
	lacunarity*=1.1;
	std::cout << "Setting lacunarity to: " << lacunarity << std::endl;
	fractionalBrownianMotion.setLacunarity(lacunarity);
	hybridMultiFractal.setLacunarity(lacunarity);
	ridgedMultiFractal.setLacunarity(lacunarity);
	updateHeightMap();
}

void PTGView::decreaseLacunarity() {
	lacunarity/=1.1;
	std::cout << "Setting lacunarity to: " << lacunarity << std::endl;
	fractionalBrownianMotion.setLacunarity(lacunarity);
	hybridMultiFractal.setLacunarity(lacunarity);
	ridgedMultiFractal.setLacunarity(lacunarity);
	updateHeightMap();
}

void PTGView::increaseOffset() {
	const float oldValue = hybridMultiFractal.getOffset();
	const float newValue = oldValue + 0.05;
	std::cout << "Setting offset to: " << newValue << std::endl;
	hybridMultiFractal.setOffset(newValue);
	updateHeightMap();
}

void PTGView::decreaseOffset() {
	const float oldValue = hybridMultiFractal.getOffset();
	const float newValue = oldValue - 0.05;
	std::cout << "Setting offset to: " << newValue << std::endl;
	hybridMultiFractal.setOffset(newValue);
	updateHeightMap();
}

void PTGView::increaseH() {
	const float oldValue = hybridMultiFractal.getH();
	const float newValue = oldValue * 1.1;
	std::cout << "Setting H to: " << newValue << std::endl;
	hybridMultiFractal.setH(newValue);
	ridgedMultiFractal.setH(newValue);
	updateHeightMap();
}

void PTGView::decreaseH() {
	const float oldValue = hybridMultiFractal.getH();
	const float newValue = oldValue / 1.1;
	std::cout << "Setting H to: " << newValue << std::endl;
	hybridMultiFractal.setH(newValue);
	ridgedMultiFractal.setH(newValue);
	updateHeightMap();
}

void PTGView::toggleBlur() {
	blurEnabled = !blurEnabled;
	std::cout << "Toggling blur: " << blurEnabled << "\n";
	updateHeightMap();
}

void PTGView::increaseIterations() {
	const unsigned int oldValue = thermalErosionTerrain.getIterations();
	unsigned int newValue = static_cast<int>(oldValue * 1.1);
	if(oldValue == newValue){
		++newValue;
	}
	std::cout << "Setting number of iterations to: " << newValue << std::endl;
	thermalErosionTerrain.setIterations(newValue);
	updateHeightMap();
}

void PTGView::decreaseIterations() {
	const unsigned int oldValue = thermalErosionTerrain.getIterations();
	unsigned int newValue = static_cast<int>(oldValue / 1.1);
	if(oldValue == newValue){
		--newValue;
	}
	std::cout << "Setting number of iterations to: " << newValue << std::endl;
	thermalErosionTerrain.setIterations(newValue);
	updateHeightMap();
}

void PTGView::increaseSlope() {
	const float oldValue = thermalErosionTerrain.getSlope();
	float newValue = oldValue * 1.1;
	std::cout << "Setting slope to: " << newValue << std::endl;
	thermalErosionTerrain.setSlope(newValue);
	updateHeightMap();
}

void PTGView::decreaseSlope() {
	const float oldValue = thermalErosionTerrain.getSlope();
	float newValue = oldValue / 1.1;
	std::cout << "Setting slope to: " << newValue << std::endl;
	thermalErosionTerrain.setSlope(newValue);
	updateHeightMap();
}

void PTGView::toggleErosion() {
	erosionEnabled = !erosionEnabled;
	std::cout << "Toggling erosion: " << erosionEnabled << "\n";
	updateHeightMap();
}

void PTGView::togglePerspective() {
	std::cout << "Toggling perspective\n";
	renderer->setPerspectiveMode(!renderer->getPerspectiveMode());
}

void PTGView::toggleTopTownView() {
	bool newValue = !renderer->getTopDownView();
	std::cout << "Toggling top down view\n";
	renderer->setTopDownView(newValue);
	renderer->setPerspectiveMode(!newValue);
}
