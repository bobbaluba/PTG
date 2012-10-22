#ifndef RENDERER_H_
#define RENDERER_H_

#include "helsing/Camera.h"
#include "helsing/MatrixStack.h"
#include "helsing/Drawable.h"
#include "helsing/HeightMap.h"
#include "helsing/Movable.h"
#include "Water.h"
#include "Actor.h"

namespace landscape {

class Renderer : public helsing::Drawable {
public:
	Renderer(uint32_t, uint32_t);
	virtual ~Renderer();
	virtual void draw();
	helsing::Camera& getCamera(){return camera;}
	virtual void resize(uint32_t width, uint32_t height);
	virtual void setTerrain(Actor* landscape){
		landscapeActor=landscape;
	}

	//Drawing functions
	static void drawVector(const helsing::Vec4& position, const helsing::Vec4& vector);
	static void drawHeightMap(const helsing::HeightMap&);

private:
	void setGLStates();
	uint32_t width, height;
	helsing::Camera camera;
	helsing::MatrixStack modelView, projection;
	Water waterActor;
	Actor* landscapeActor;
};

}

#endif /* RENDERER_H_ */
