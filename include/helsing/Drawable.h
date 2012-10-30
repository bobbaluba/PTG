/*
 * Drawable.h
 *
 *  Created on: 15. sep. 2012
 *      Author: johan
 */
#ifndef DRAWABLE_H_
#define DRAWABLE_H_

namespace helsing {

class Drawable {
public:
	virtual void draw() = 0;
	virtual ~Drawable() {
	}
};

}

#endif


