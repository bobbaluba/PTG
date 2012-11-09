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
 * I implemented this class to try to get rid of some of the artifacts seen in DiamondSquareTerrain
 *
 */
class GaussianBlurTerrain: public Terrain {
public:
	explicit GaussianBlurTerrain(const Terrain& source);
	virtual ~GaussianBlurTerrain();
};

} // namespace ptg
#endif // GAUSSIANBLURTERRAIN_HPP
