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
 * It is good idea to use a heightmap that is close to what you want as source to avoid unnecessary many
 * iterations.
 *
 */
class ThermalErosionTerrain: public Terrain {
public:
	explicit ThermalErosionTerrain(Terrain* source);
	virtual ~ThermalErosionTerrain();
	virtual helsing::HeightMap generateHeightMap(unsigned int gridPoints, float gridSpacing);
	virtual void setSource(Terrain*);
private:
	Terrain* source;
	unsigned int steps;
};

} // namespace ptg
#endif // THERMALEROSIONTERRAIN_HPP
