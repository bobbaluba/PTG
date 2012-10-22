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

namespace landscape {

class LandscapeApplication: public helsing::Application {
public:
	LandscapeApplication(const ApplicationSettings& = ApplicationSettings());
	virtual ~LandscapeApplication(){delete worldView;}
	virtual void onInit();
	virtual void onRender();
	virtual void onResize(uint32_t width, uint32_t height){
		worldView->resize(width,height);
	}
	virtual bool handleEvent(const sf::Event&);
private:
	Renderer* worldView;
	bool flymode;
	uint32_t heightMapSize;
};

} /* namespace landscape */
#endif /* LANDSCAPEAPPLICATION_H_ */
