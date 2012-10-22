/*
 * Seedable.h
 *
 *  Created on: 22. okt. 2012
 *      Author: johan
 */

#ifndef SEEDABLE_H_
#define SEEDABLE_H_

class Seedable {
public:
	explicit Seedable(unsigned int seed=0):seed(seed){}
	virtual ~Seedable(){};
private:
	unsigned int seed;
};

#endif /* SEEDABLE_H_ */
