/**
 * @file BasicScene.hpp
 * @date 25. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef BASICSCENE_HPP
#define BASICSCENE_HPP

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

#endif /* BASICSCENE_HPP */
