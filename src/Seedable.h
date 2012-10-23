/**
 * Seedable.h
 *
 * @date 2012
 * @author Johan Helsing
 *
 * @brief This is intended as an abstract interface class for objects that can be seeded and reseeded
 *
 */

#ifndef SEEDABLE_H_
#define SEEDABLE_H_

class Seedable {
public:
	explicit Seedable(unsigned int seed=0):s(seed){}
	virtual ~Seedable(){};
	virtual void seed(unsigned int seed){s=seed; onReSeed(seed);}
protected:
	/// This function is called when the Seedable is reseeded
	virtual void onReSeed(unsigned int seed) {};
private:
	unsigned int s;
};

#endif /* SEEDABLE_H_ */
