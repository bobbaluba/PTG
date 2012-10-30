/*
 * Actor.h
 *
 *  Created on: 14. sep. 2012
 *      Author: johan
 */

#ifndef ACTOR_H_
#define ACTOR_H_

#include <helsing/Drawable.h>
#include <helsing/Movable.h>


class Actor: public helsing::Drawable, public virtual helsing::Movable {
public:
	Actor();
	virtual ~Actor();
	virtual void draw(){}
private:

};

#endif /* ACTOR_H_ */
