/**
 * @file LandscapeApplication.hpp
 * @date 25. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef LANDSCAPEAPPLICATION_HPP
#define LANDSCAPEAPPLICATION_HPP

#include "SceneApplication.hpp"
#include "Renderer.hpp"

#include <helsing/Application.hpp>

#include <ptg/DiamondSquareTerrain.hpp>
#include <ptg/MidpointDisplacementTerrain.hpp>
#include <ptg/Continuous2DSignalTerrain.hpp>
#include <ptg/PerlinNoise.hpp>
#include <ptg/FractionalBrownianMotion.hpp>

namespace ptg {

class LandscapeApplication: public helsing::Application {
public:
	LandscapeApplication(const ApplicationSettings& = ApplicationSettings());
	virtual ~LandscapeApplication() {
		delete renderer;
	}
	virtual void onInit();
	virtual void onRender();
	virtual void onResize(uint32_t width, uint32_t height) {
		renderer->resize(width, height);
	}
	virtual bool handleEvent(const sf::Event&);
	/** Set the current terrain the application is displaying
	 * Does not take ownership of the terrain
	 */
	virtual void setTerrain(Terrain* terrain);
	virtual void setHeightMapSize(unsigned int size);
private:
	virtual void increaseDetail();
	virtual void decreaseDetail();
	virtual void increaseAmplitude();
	virtual void decreaseAmplitude();
	virtual void increaseGain();
	virtual void decreaseGain();
	virtual void raiseWater(float amount);
	virtual void updateHeightMap();
	Renderer* renderer;
	bool flymode;
	unsigned int heightMapSize;
	Terrain* terrain;
	float amplitude;
	float gain;
	float waterLevel;
	MidpointDisplacementTerrain midpointDisplacementTerrain;
	DiamondSquareTerrain diamondSquareTerrain;
	Continuous2DSignalTerrain continuous2DSignalTerrain;
	PerlinNoise perlinNoise;
	FractionalBrownianMotion fractionalBrownianMotion;
};

} /* namespace landscape */
#endif /* LANDSCAPEAPPLICATION_HPP */
