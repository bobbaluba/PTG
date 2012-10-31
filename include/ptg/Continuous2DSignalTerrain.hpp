/**
 * @file Continuous2DSignalTerrain.hpp
 * @date 26. okt. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef CONTINUOUS2DSIGNALTERRAIN_HPP
#define CONTINUOUS2DSIGNALTERRAIN_HPP

#include <ptg/Terrain.hpp>
#include <ptg/Continuous2DSignal.hpp>

namespace ptg {

/**
 * @brief Terrain using a Continuous2DSignal as source
 */
class Continuous2DSignalTerrain: public ptg::Terrain {
public:
	Continuous2DSignalTerrain(unsigned int seed=0);
	virtual ~Continuous2DSignalTerrain();

	///@brief Set source signal of the terrain
	virtual void setSignal(Continuous2DSignal* signal);

	virtual helsing::HeightMap generateHeightMap(unsigned int gridPoints, float gridSpacing);
	virtual void onReSeed(unsigned int seed);

	///@brief Set the amplitude of the terrain
	virtual void setAmplitude(float amplitude){this->amplitude=amplitude;}
private:
	Continuous2DSignal* signal;
	float amplitude;
};

} // namespace ptg
#endif // CONTINUOUS2DSIGNALTERRAIN_HPP
