#ifndef RENDERER_H_
#define RENDERER_H_

#include <helsing/Camera.hpp>
#include <helsing/MatrixStack.hpp>
#include <helsing/HeightMap.hpp>
#include <helsing/Movable.hpp>
#include "Water.hpp"
#include "Actor.hpp"

namespace ptg {

class Renderer{
public:
	Renderer(uint32_t, uint32_t);
	virtual ~Renderer();
	virtual void draw();
	helsing::Camera& getCamera(){return camera;}
	virtual void resize(uint32_t width, uint32_t height);
	virtual void setHeightMap(helsing::HeightMap* heightMap);
	virtual void setWaterLevel(float level){waterLevel=level;}

	//Drawing functions
	static void drawVector(const helsing::Vec4& position, const helsing::Vec4& vector);
	static void drawHeightMap(const helsing::HeightMap&);

private:
	void setGLStates();
	uint32_t width, height;
	helsing::Camera camera;
	helsing::MatrixStack modelView, projection;
	Water water;
	float waterLevel;
	helsing::HeightMap* heightMap;
};

}

#endif /* RENDERER_H_ */
