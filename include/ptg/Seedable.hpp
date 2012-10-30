/**
 * Seedable.hpp
 *
 * @date 2012
 * @author Johan Klokkhammer Helsing
 *
 */

#ifndef SEEDABLE_H_
#define SEEDABLE_H_

namespace ptg {

/// @brief An abstract interface class for objects that can be seeded and reseeded
class Seedable {
public:
	explicit Seedable(unsigned int seed=0):s(seed){}
	virtual ~Seedable(){};
	virtual void seed(unsigned int seed){s=seed; onReSeed(seed);}
	virtual unsigned int getSeed() const {return s;}
protected:
	/// This function is called when the Seedable is reseeded
	virtual void onReSeed(unsigned int seed) {};
private:
	unsigned int s;
};

}// namespace ptg
#endif /* SEEDABLE_H_ */
