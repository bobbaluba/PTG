/**
 * @file Water.hpp
 * @date 15. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef WATER_HPP
#define WATER_HPP

#include <helsing/Drawable.hpp>
#include <helsing/Shader.hpp>

class Water: public helsing::Drawable {
public:
	Water(float size);
	virtual ~Water(){}
	virtual void draw(const helsing::Mat4& modelViewMatrix, const helsing::Mat4& projectionMatrix);
	virtual void setSize(float size){this->size=size;}
private:
	float size;
	helsing::Shader shader;
	unsigned int vaoId;
};

#endif /* WATER_HPP */
