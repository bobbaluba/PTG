/**
 * @file ThermalErosionTerrain.hpp
 * @date 12. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef THERMALEROSIONTERRAIN_HPP
#define THERMALEROSIONTERRAIN_HPP

#include <ptg/Terrain.hpp>

namespace ptg {

/**
 * @brief Decorator for other terrains, takes another terrain as it's source and applies thermal erosion
 *
 * Uses a cellular automata with a Von Neumann pattern to simulate rocks cracking and sliding
 * down hills.
 *
 * It is good idea to use a heightmap that is close to what you want as source to avoid unnecessary many
 * iterations.
 *
 * Complexity
 * ----------
 *
 *     THETA(WIDTH^2*iterations)
 *
 */
class ThermalErosionTerrain: public Terrain {
public:
	explicit ThermalErosionTerrain(Terrain* source);
	virtual ~ThermalErosionTerrain();
	virtual helsing::HeightMap generateHeightMap(unsigned int gridPoints, float gridSpacing);

	/// @brief sets the source terrain to transform
	virtual void setSource(Terrain*);

	/// @brief Sets the number of iterations to run the cellular automata
	virtual void setIterations(unsigned int iterations){this->iterations = iterations;}
	virtual unsigned int getIterations() const {return iterations;}

	/// @brief sets how steep the terrain must be before heights will begin to transfer downwards
	virtual void setSlope(float slope){this->slope=slope;}
	virtual float getSlope() const {return slope;}
private:
	Terrain* source;
	unsigned int iterations;
	float slope;
};

} // namespace ptg
#endif // THERMALEROSIONTERRAIN_HPP
