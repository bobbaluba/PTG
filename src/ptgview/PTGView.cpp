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
		SFMLApplication(settings),
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

void PTGView::onKeyPressed(helsing::Keyboard::Key key) {
	switch(key){
	case helsing::Keyboard::ESCAPE:
		stop();
		break;
	case helsing::Keyboard::RETURN:
	case helsing::Keyboard::SPACE:
		reseedTerrain();
		break;
	case helsing::Keyboard::P:
		increaseDetail();
		break;
	case helsing::Keyboard::O:
		decreaseDetail();
		break;
	case helsing::Keyboard::L:
		increaseAmplitude();
		break;
	case helsing::Keyboard::K:
		decreaseAmplitude();
		break;
	case helsing::Keyboard::M:
		increaseGain();
		break;
	case helsing::Keyboard::N:
		decreaseGain();
		break;
	case helsing::Keyboard::B:
		toggleBlur();
		break;
	case helsing::Keyboard::E:
		toggleErosion();
		break;
	case helsing::Keyboard::U:
		decreaseOctaves();
		break;
	case helsing::Keyboard::I:
		increaseOctaves();
		break;
	case helsing::Keyboard::Z:
		decreaseOffset();
		break;
	case helsing::Keyboard::X:
		increaseOffset();
		break;
	case helsing::Keyboard::C:
		decreaseLacunarity();
		break;
	case helsing::Keyboard::V:
		increaseLacunarity();
		break;
	case helsing::Keyboard::Q:
		togglePerspective();
		break;
	case helsing::Keyboard::TAB:
		toggleTopTownView();
		break;
	case helsing::Keyboard::COMMA:
		decreaseH();
		break;
	case helsing::Keyboard::PERIOD:
		increaseH();
		break;
	case helsing::Keyboard::F1:
		decreaseIterations();
		break;
	case helsing::Keyboard::F2:
		increaseIterations();
		break;
	case helsing::Keyboard::F3:
		decreaseSlope();
		break;
	case helsing::Keyboard::F4:
		increaseSlope();
		break;
	case helsing::Keyboard::F5:
		cycleShaders();
		break;
	case helsing::Keyboard::NUMBER_1:
		std::cout << "Switching to midpoint displacement terrain\n";
		setTerrain(&midpointDisplacementTerrain);
		break;
	case helsing::Keyboard::NUMBER_2:
		std::cout << "Switching to diamond square terrain\n";
		setTerrain(&diamondSquareTerrain);
		break;
	case helsing::Keyboard::NUMBER_3:
		std::cout << "Switching to helsing square terrain\n";
		setTerrain(&helsingSquareTerrain);
		break;
	case helsing::Keyboard::NUMBER_4:
		std::cout << "Switching to perlin noise terrain\n";
		continuous2DSignalTerrain.setSignal(&perlinNoise);
		setTerrain(&continuous2DSignalTerrain);
		break;
	case helsing::Keyboard::NUMBER_5:
		std::cout << "Switching to fractional brownian perlin noise terrain\n";
		fractionalBrownianMotion.setBaseNoise(&perlinNoise);
		continuous2DSignalTerrain.setSignal(&fractionalBrownianMotion);
		setTerrain(&continuous2DSignalTerrain);
		break;
	case helsing::Keyboard::NUMBER_6:
		std::cout << "Switching to value noise terrain\n";
		continuous2DSignalTerrain.setSignal(&valueNoise);
		setTerrain(&continuous2DSignalTerrain);
		break;
	case helsing::Keyboard::NUMBER_7:
		std::cout << "Switching to fractional brownian value noise terrain\n";
		fractionalBrownianMotion.setBaseNoise(&valueNoise);
		continuous2DSignalTerrain.setSignal(&fractionalBrownianMotion);
		setTerrain(&continuous2DSignalTerrain);
		break;
	case helsing::Keyboard::NUMBER_8:
		std::cout << "Switching to hybrid multifractal terrain with perlin noise\n";
		hybridMultiFractal.setBaseNoise(&perlinNoise);
		continuous2DSignalTerrain.setSignal(&hybridMultiFractal);
		setTerrain(&continuous2DSignalTerrain);
		break;
	case helsing::Keyboard::NUMBER_9:
		std::cout << "Switching to ridged multi fractal terrain with perlin noise\n";
		ridgedMultiFractal.setBaseNoise(&perlinNoise);
		continuous2DSignalTerrain.setSignal(&ridgedMultiFractal);
		setTerrain(&continuous2DSignalTerrain);
		break;
	default:
		//don't do anything
		break;
	}
}

void PTGView::onMousePressed(bool left) {
	if(left){
		flymode = !flymode;
		window->setMouseCursorVisible(!flymode);
	}
}

void PTGView::onRender(){
	Camera& camera = renderer->getCamera();

	//camera movement
	const float speed = 0.5f; //todo scale with time
	if(isKeyDown(helsing::Keyboard::W)){
		camera.forward(speed);
	}
	if(isKeyDown(helsing::Keyboard::S)){
		camera.forward(-speed);
	}
	if(isKeyDown(helsing::Keyboard::A)){
		camera.right(-speed);
	}
	if(isKeyDown(helsing::Keyboard::D)){
		camera.right(speed);
	}
	if(isKeyDown(helsing::Keyboard::R)){
		camera.up(speed);
	}
	if(isKeyDown(helsing::Keyboard::F)){
		camera.up(-speed);
	}

	//Water levels
	const float waterSpeed=0.1f; //todo scale with time
	if (isKeyDown(helsing::Keyboard::T)) {
		raiseWater(waterSpeed);
	}
	if (isKeyDown(helsing::Keyboard::G)) {
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

void PTGView::cycleShaders() {
	if(currentShader == Renderer::PHONG){
		std::cout << "Using goraud shading\n";
		currentShader = Renderer::GORAUD;
	} else {
		std::cout << "Using phong shading\n";
		currentShader = Renderer::PHONG;
	}
	renderer->setShaderType(currentShader);
}
