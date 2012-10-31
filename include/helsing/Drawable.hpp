/**
 * @file Drawable.hpp
 * @date 15. sep. 2012
 * @author Johan Klokkhammer Helsing
 */
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

namespace helsing {

class Drawable {
public:
	virtual void draw() = 0;
	virtual ~Drawable() {
	}
};

}

#endif


