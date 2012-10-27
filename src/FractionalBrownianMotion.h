/*
 * FractionalBrownianMotion.h
 *
 *  Created on: 27. okt. 2012
 *      Author: johan
 */

#ifndef FRACTIONALBROWNIANMOTION_H_
#define FRACTIONALBROWNIANMOTION_H_

#include "Continuous2DSignal.h"

namespace ptg {

class FractionalBrownianMotion: public ptg::Continuous2DSignal {
public:
	FractionalBrownianMotion(unsigned int seed=0);
	virtual ~FractionalBrownianMotion();
private:
};

} /* namespace ptg */
#endif /* FRACTIONALBROWNIANMOTION_H_ */
