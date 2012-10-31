/**
 * @file Actor.hpp
 * @date 14. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <helsing/Drawable.hpp>
#include <helsing/Movable.hpp>


class Actor: public helsing::Drawable, public virtual helsing::Movable {
public:
	Actor();
	virtual ~Actor();
	virtual void draw(){}
private:

};

#endif /* ACTOR_HPP */
