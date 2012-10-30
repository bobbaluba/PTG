/*
 * Scene.h
 *
 * abstract/interface class
 *
 *  Created on: 14. sep. 2012
 *      Author: johan
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <helsing/Drawable.h>

#include <SFML/Graphics.hpp>

class Scene: public helsing::Drawable {
public:
	virtual ~Scene(){}
	virtual void hide(){}
	virtual void show(){}
	virtual void render() = 0;
	virtual bool handleEvent(const sf::Event&){return false;}
};

#endif /* SCENE_H_ */
