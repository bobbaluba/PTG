/*
 * BasicScene.hpp
 *
 *  Created on: 25. sep. 2012
 *      Author: Johan Klokkhammer Helsing
 */

#ifndef BASICSCENE_H_
#define BASICSCENE_H_

#include "Scene.hpp"

class BasicScene: public Scene {
public:
	BasicScene();
	virtual ~BasicScene();
	virtual void addDrawable(Drawable*);
	virtual void render();
private:
	std::vector<Drawable*> drawables;
};

#endif /* BASICSCENE_H_ */
