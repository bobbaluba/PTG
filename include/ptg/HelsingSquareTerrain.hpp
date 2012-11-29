/**
 * @file HelsingSquareTerrain.hpp
 * @date 11. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef HELSINGSQUARETERRAIN_HPP
#define HELSINGSQUARETERRAIN_HPP

#include <ptg/Terrain.hpp>

namespace ptg {

/** @brief Terrain generated using a modified version of the diamond square algorithm.
 *
 * Solves some of the artifacts that occur in the diamond square algorithm, but introduces pointy tops
 * The pointy tops can be removed by using a blurring filter as an intermediate or last step.
 *
 * Complexity
 * ----------
 * Since this is just a minor modification of diamond square, the complexity is the same
 *
 *     THETA(WIDTH^2)
 *
 * Limitations and Artifacts
 * -------------------------
 * The size of the grid has to be 2^n+1
 * The points inside an area depends on all the points along the edges,
 * this makes inconvenient to calculate just a portion of the heightMap.
 *
 * In terms of artifacts and your preferences, the algorithm is a little better than diamond square.
 * The ridges are gone, but mountain tops appear pinched.
 */
class HelsingSquareTerrain: public ptg::Terrain {
public:
	/**
	 * @param gain, how fast the amplitude decreases each octave, low (<0.5) will create smooth terrains
	 */
	explicit HelsingSquareTerrain(float gain=0.5, unsigned int seed=0);
	virtual ~HelsingSquareTerrain();
	virtual helsing::HeightMap generateHeightMap(unsigned int gridPoints, float gridSpacing);
	///@brief Set the amplitude. The amplitude is basically just the scaling factor
	virtual void setAmplitude(float amplitude){
		this->amplitude=amplitude;
	}
	virtual float getAmplitude() const {return amplitude;}
	virtual void setGain(float gain){this->gain=gain;}
	HelsingSquareTerrain(const HelsingSquareTerrain&) = default;
	HelsingSquareTerrain & operator=(const HelsingSquareTerrain&) = default;
private:
	float whiteNoise() const;
	float amplitude;
	float gain;
};

} // namespace ptg
#endif // HELSINGSQUARETERRAIN_HPP
