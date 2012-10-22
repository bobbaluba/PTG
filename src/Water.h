/*
 * Water.h
 *
 *  Created on: 15. sep. 2012
 *      Author: johan
 */

#ifndef WATER_H_
#define WATER_H_

#include "helsing/Drawable.h"

class Water: public helsing::Drawable {
public:
	Water(float size):size(size){}
	virtual ~Water(){}
	virtual void draw();
private:
	float size;
};

#endif /* WATER_H_ */
