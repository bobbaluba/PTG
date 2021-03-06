/**
 * @file DiamondSquareTerrain.hpp
 * @date 25. okt. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef DIAMONDSQUARETERRAIN_HPP
#define DIAMONDSQUARETERRAIN_HPP

#include <ptg/Terrain.hpp>

namespace ptg {

/** @brief Terrain generated using the diamond square algorithm
 *
 * Solves some of the artifacts that occur in midpoint displacement
 *
 * Complexity
 * ----------
 * Since this is just a minor modification of midpoint displacement, the complexity is the same
 *
 *     THETA(WIDTH^2)
 *
 * Limitations and Artifacts
 * -------------------------
 * The size of the grid has to be 2^n+1
 * This is and explicit procedural alrogithm, meaning it isn't possible to directly query for the value at a particular point.
 * The points inside an area depends on all the points along the edges,
 * this makes it inconvenient to calculate just a portion of the heightMap.

 * In terms of artifacts, the algorithm is a little better than midpoint displacement.
 * Mountain tops appear pinched, though. This might be fixed by using a different displacement
 * function.
 *
 */
class DiamondSquareTerrain: public ptg::Terrain {
public:
	/**
	 * @param gain, how fast the amplitude decreases each octave, low (<0.5) will create smooth terrains
	 */
	explicit DiamondSquareTerrain(float gain=0.5, unsigned int seed=0);
	virtual ~DiamondSquareTerrain();
	virtual helsing::HeightMap generateHeightMap(unsigned int gridPoints, float gridSpacing);
	///@brief Set the amplitude. The amplitude is basically just the scaling factor
	virtual void setAmplitude(float amplitude){
		this->amplitude=amplitude;
	}
	virtual float getAmplitude() const {return amplitude;}
	virtual void setGain(float gain){this->gain=gain;}

	DiamondSquareTerrain(const DiamondSquareTerrain&) = default;
	DiamondSquareTerrain & operator=(const DiamondSquareTerrain&) = default;
private:
	float whiteNoise() const;
	float amplitude;
	float gain;
};

} /* namespace ptg */
#endif /* DIAMONDSQUARETERRAIN_HPP */
