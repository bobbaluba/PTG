/*
 * LandscapeApplication.h
 *
 *  Created on: 25. sep. 2012
 *      Author: johan
 */

#ifndef LANDSCAPEAPPLICATION_H_
#define LANDSCAPEAPPLICATION_H_

#include "helsing/Application.h"
#include "SceneApplication.h"
#include "Renderer.h"
#include "Terrain.h"

#include <helsing/HeightMap.h>

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
	 * Takes ownership of the supplied terrain, responsible for deleting it
	 */
	virtual void setTerrain(Terrain* terrain);
	virtual void setHeightMapSize(unsigned int size);
private:
	virtual void increaseDetail();
	virtual void decreaseDetail();
	virtual void updateHeightMap();
	Renderer* renderer;
	bool flymode;
	unsigned int heightMapSize;
	Terrain* terrain;
};

} /* namespace landscape */
#endif /* LANDSCAPEAPPLICATION_H_ */
