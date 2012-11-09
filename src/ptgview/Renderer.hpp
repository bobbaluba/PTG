/**
 * @file Renderer.hpp
 * @date 2012
 * @author Johan Klokkhammer Helsing
 */
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Water.hpp"
#include "TerrainMesh.hpp"

#include <helsing/HeightMap.hpp>
#include <helsing/Camera.hpp>
#include <helsing/MatrixStack.hpp>
#include <helsing/Movable.hpp>

/** @brief Encapsulates drawing related parts of the PTGView application
 *
 * Should be regarded as the View part of the MVC pattern
 */
class Renderer{
public:
	Renderer(uint32_t width, uint32_t height);
	virtual ~Renderer();
	virtual void draw();

	/// @brief get handle for the Camera
	helsing::Camera& getCamera(){return camera;}

	/// @brief corrects aspect ratio when the viewport has changed
	virtual void resize(uint32_t width, uint32_t height);

	/// @brief select a new heightMap for drawing
	virtual void setHeightMap(helsing::HeightMap* heightMap);

	/// @brief sets the y value of the water
	virtual void setWaterLevel(float level){waterLevel=level;}

	//Drawing functions
	static void drawVector(const helsing::Vec4& position, const helsing::Vec4& vector);
private:
	void setGLStates();
	uint32_t width, height;
	helsing::Camera camera;
	helsing::MatrixStack modelView, projection;
	Water water;
	float waterLevel;
	TerrainMesh* terrainMesh;
};

#endif /* RENDERER_HPP */
