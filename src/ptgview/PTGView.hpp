/**
 * @file PTGView.hpp
 * @date 25. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef PTGVIEW_HPP
#define PTGVIEW_HPP

#include "Renderer.hpp"

#include <helsing/SFMLApplication.hpp>

#include <ptg/DiamondSquareTerrain.hpp>
#include <ptg/MidpointDisplacementTerrain.hpp>
#include <ptg/Continuous2DSignalTerrain.hpp>
#include <ptg/PerlinNoise.hpp>
#include <ptg/FractionalBrownianMotion.hpp>
#include <ptg/GaussianBlurTerrain.hpp>
#include <ptg/HelsingSquareTerrain.hpp>
#include <ptg/ValueNoise.hpp>
#include <ptg/HybridMultiFractal.hpp>
#include <ptg/RidgedMultiFractal.hpp>
#include <ptg/ThermalErosionTerrain.hpp>

using namespace ptg;

/** @brief An Application for generating and viewing terrains using the PTG library
 *
 */
class PTGView: public helsing::SFMLApplication {
public:
	explicit PTGView(const ApplicationSettings& = ApplicationSettings());
	virtual ~PTGView() {
		delete renderer;
	}
	virtual void onInit();
	virtual void onRender();
	virtual void onResize(uint32_t width, uint32_t height) {renderer->resize(width, height);}
	virtual void onKeyPressed(helsing::Keyboard::Key);
	virtual void onMousePressed(bool left);
	/** Set the current terrain the application is displaying
	 * Does not take ownership of the terrain
	 */
	virtual void setTerrain(Terrain* terrain);
	virtual void setHeightMapSize(unsigned int size);
private:
	virtual void reseedTerrain();
	virtual void increaseDetail();
	virtual void decreaseDetail();
	virtual void increaseAmplitude();
	virtual void decreaseAmplitude();
	virtual void increaseGain();
	virtual void decreaseGain();
	virtual void increaseOctaves();
	virtual void decreaseOctaves();
	virtual void increaseLacunarity();
	virtual void decreaseLacunarity();
	virtual void increaseOffset(); //for hybrid multifractal
	virtual void decreaseOffset();
	virtual void increaseH(); //for multifractals
	virtual void decreaseH();
	virtual void increaseIterations(); //for thermal erosion
	virtual void decreaseIterations();
	virtual void increaseSlope(); //for thermal erosion
	virtual void decreaseSlope();
	virtual void raiseWater(float amount);
	virtual void updateHeightMap();
	virtual void toggleBlur();
	virtual void toggleErosion();
	virtual void togglePerspective(); //switch between orthogonal and perspective projection
	virtual void toggleTopTownView();
	virtual void cycleShaders(); //cycle between different shaders
	Renderer* renderer;
	bool flymode;
	unsigned int heightMapSize;
	Terrain* terrain;
	float amplitude;
	float gain;
	float lacunarity;
	float waterLevel;
	MidpointDisplacementTerrain midpointDisplacementTerrain;
	DiamondSquareTerrain diamondSquareTerrain;
	Continuous2DSignalTerrain continuous2DSignalTerrain;
	PerlinNoise perlinNoise;
	FractionalBrownianMotion fractionalBrownianMotion;
	GaussianBlurTerrain gaussianBlurTerrain;
	HelsingSquareTerrain helsingSquareTerrain;
	ValueNoise valueNoise;
	HybridMultiFractal hybridMultiFractal;
	RidgedMultiFractal ridgedMultiFractal;
	ThermalErosionTerrain thermalErosionTerrain;
	bool blurEnabled;
	bool erosionEnabled;
	Renderer::ShaderType currentShader;
};

#endif // PTGVIEW_HPP
