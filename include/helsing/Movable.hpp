/*
 * Movable.hpp
 *
 *  Created on: 14. sep. 2012
 *      Author: Johan Klokkhammer Helsing
 */

#ifndef MOVABLE_H_
#define MOVABLE_H_

#include <helsing/hmath.hpp>

namespace helsing {

class Movable {
public:
	Movable():position(helsing::Vec4::origin()){}
	Movable(const helsing::Vec4& position):position(position){}
	virtual ~Movable(){}
	virtual helsing::Vec4 getPosition(){return position;}
protected:
	helsing::Vec4 position;
};

} /* namespace gfx */
#endif /* POSITION_H_ */
