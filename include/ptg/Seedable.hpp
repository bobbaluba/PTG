/**
 * @file Seedable.hpp
 * @date 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef SEEDABLE_HPP
#define SEEDABLE_HPP

namespace ptg {

/**
 * @brief An abstract interface class for objects that can be seeded and reseeded
 */
class Seedable {
public:
	explicit Seedable(unsigned int seed=0):s(seed){}
	virtual ~Seedable(){};

	/**
	 * @brief Reeseed the seedable
	 * @param seed new seed
	 */
	virtual void seed(unsigned int seed){s=seed; onReSeed(seed);}

	/**
	 * @brief Get the current seed
	 */
	virtual unsigned int getSeed() const {return s;}
protected:
	/**
	 * @brief Template function that reseedable subclasses should implement
	 *
	 * Called when the seedable is reseeded
	 * @param seed the new seed.
	 */
	virtual void onReSeed(unsigned int seed) {};
private:
	unsigned int s;
};

} //namespace ptg
#endif //SEEDABLE_HPP
