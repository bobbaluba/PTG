/**
 * @file Water.hpp
 * @date 15. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef WATER_HPP
#define WATER_HPP

#include <helsing/Drawable.hpp>

class Water: public helsing::Drawable {
public:
	Water(float size):size(size){}
	virtual ~Water(){}
	virtual void draw();
	virtual void setSize(float size){this->size=size;}
private:
	float size;
};

#endif /* WATER_HPP */
