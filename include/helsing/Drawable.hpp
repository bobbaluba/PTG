/**
 * @file Drawable.hpp
 * @date 15. sep. 2012
 * @author Johan Klokkhammer Helsing
 */
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <helsing/math/Mat4.hpp>

namespace helsing {

class Drawable {
public:
	virtual void draw(const helsing::Mat4& modelViewMatrix, const helsing::Mat4& projectionMatrix) = 0;
	virtual ~Drawable() {
	}
};

}

#endif


