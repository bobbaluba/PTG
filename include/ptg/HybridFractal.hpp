/**
 * @file HybridFractal.hpp
 * @date 12. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef HYBRIDFRACTAL_HPP
#define HYBRIDFRACTAL_HPP

#include <ptg/Continuous2DSignal.hpp>

#include <vector>

namespace ptg {

/** @brief Fractal noise generated using hybrid fractional brownian motion
 *
 * As described in this paper:
 * http://www8.cs.umu.se/kurser/TDBD12/HT01/papers/MusgraveTerrain00.pdf
 *
 * THIS IS THE DOCUMENTATION FOR FRACTIONAL BROWNIAN MOTION. The hybrid fractal is a slightly modified version
 *
 * The algorithm takes a Continuous2DSignal as its source to create a fractal noise
 * The noise is scaled to different frequencies and amplitudes, and these are added together.
 *
 * The algorithm is an easy way to create more interesting noise out of simple smoothed white noise,
 * such as Perlin noise or value noise.
 *
 * Complexity
 * ----------
 * The complexity depends greatly on the choice of noise function.
 * If the noise function's complexity is f(n), the complexity of fbm is:
 *
 *     THETA(WIDTH^2*octaves*f(n))
 *
 * Where octaves is the number "layers" added together. This will usually be a number between 3 and 9.
 *
 * Limitations and Artifacts when used as terrain
 * ----------------------------------------------
 * Depending on the choice of noise function, there may be a number of visible artifacts.
 * If your noise signal is repeating over a relatively short period, there will be visible artifacts in
 * the resulting terrain. The reason for this, is that when we are shading terrain, the diffuse lighting
 * depends on the derivative of the terrain, and therefore small changes will be visible.
 *
 * To solve this, you might either:
 *  * Adjust gain so it's low enough that the highest octaves barely change the terrain values.
 *  * Reduce the number of octaves, so the terrain won't repeat itself too much in the visible distance.
 *  * Add a post-filter with diamond-square displacement to do the smallest levels of displacement,
 *    as diamond square doesn't repeat itself, even on the smallest layers.
 *  * Reduce specular/diffuse lighting and rely more on textures to show the tiniest bumps in the terrain.
 */
class HybridFractal: public ptg::Continuous2DSignal {
public:
	HybridFractal(unsigned int seed=0);
	virtual ~HybridFractal();
	virtual float get(float x, float y);
	virtual void onReSeed(unsigned int seed);

	/** @brief Sets the base noise function for the algorithm
	 * suitable choices are ValueNoise or Perlin Noise
	 */
	virtual void setBaseNoise(Continuous2DSignal* signal){baseNoise=signal;}

	/** @brief Set the "depth" of the fractal noise.
	 * Sets how many "layers" of noise we are going to add together.
	 * Typical values lie between 3 and 9.
	 */
	virtual void setOctaves(unsigned int octaves){this->octaves=octaves; initExponents();}

	// @brief Gets number of octaves, see setOctaves
	virtual unsigned int getOctaves() const {return octaves;}

	/** @brief sets the lacunarity
	 * this is the relation between the frequency of succesive layers in fbm-like algorithms
	 */
	virtual void setLacunarity(float lacunarity){this->lacunarity=lacunarity; initExponents();}
	virtual float getLacunarity() const {return lacunarity;}
private:
	void initExponents();
	Continuous2DSignal* baseNoise;
	unsigned int octaves;
	float lacunarity;
	float H;
	std::vector<float> exponents;
};

} // namespace ptg
#endif // HYBRIDFRACTAL_HPP
