/*
 * Actor.hpp
 *
 *  Created on: 14. sep. 2012
 *      Author: Johan Klokkhammer Helsing
 */

#ifndef ACTOR_H_
#define ACTOR_H_

#include <helsing/Drawable.hpp>
#include <helsing/Movable.hpp>


class Actor: public helsing::Drawable, public virtual helsing::Movable {
public:
	Actor();
	virtual ~Actor();
	virtual void draw(){}
private:

};

#endif /* ACTOR_H_ */
