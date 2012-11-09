/**
 * @file GaussianBlurTerrain.hpp
 * @date 9. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef GAUSSIANBLURTERRAIN_HPP
#define GAUSSIANBLURTERRAIN_HPP

#include <ptg/Terrain.hpp>

namespace ptg {

/**
 * @brief Decorator for other terrains, takes another terrain as it's source and applies gaussian blur
 *
 * I implemented this class to try to get rid of some of the pointy tops seen in DiamondSquareTerrain
 *
 */
class GaussianBlurTerrain: public Terrain {
public:
	explicit GaussianBlurTerrain(Terrain* source);
	virtual ~GaussianBlurTerrain();
	virtual helsing::HeightMap generateHeightMap(unsigned int gridPoints, float gridSpacing);
	virtual void setSource(Terrain*);
private:
	Terrain* source;
};

} // namespace ptg
#endif // GAUSSIANBLURTERRAIN_HPP
