/**
 * @file Scene.hpp
 * @date 14. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef SCENE_HPP
#define SCENE_HPP

#include <helsing/Drawable.hpp>

#include <SFML/Graphics.hpp>

/// @brief abstract/interface class
class Scene: public helsing::Drawable {
public:
	virtual ~Scene(){}
	virtual void hide(){}
	virtual void show(){}
	virtual void render() = 0;
	virtual bool handleEvent(const sf::Event&){return false;}
};

#endif // SCENE_HPP
