/**
 * @file Movable.hpp
 * @date 14. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include <helsing/hmath.hpp>

namespace helsing {

class Movable {
public:
	explicit Movable():position(helsing::Vec4::origin()){}
	explicit Movable(const helsing::Vec4& position):position(position){}
	virtual ~Movable(){}
	virtual helsing::Vec4 getPosition(){return position;}
protected:
	helsing::Vec4 position;
};

} /* namespace gfx */
#endif /* POSITION_HPP */
