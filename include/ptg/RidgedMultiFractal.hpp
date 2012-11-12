/**
 * @file HybridMultiFractal.hpp
 * @date 12. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef HYBRIDMULTIFRACTAL_HPP
#define RIDGEDMULTIFRACTAL_HPP

#include <ptg/Continuous2DSignal.hpp>

#include <vector>

namespace ptg {

/** @brief Fractal noise generated using ridged multi fractal as described by
 * Musgrave
 */
class RidgedMultiFractal: public ptg::Continuous2DSignal {
public:
	RidgedMultiFractal(unsigned int seed=0);
	virtual ~RidgedMultiFractal();
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

	/** @brief sets the offset. This value is added to the noise before multiplications
	 *
	 * Assuming the noise value varies from -1 to 1, 0.7 will probably be a decent value
	 */
	virtual void setOffset(float offset){this->offset=offset;}
	virtual float getOffset() const {return offset;}

	/** @brief sets the H value
	 *
	 * This value controls how the amplitude changes from octave to octave.
	 * A high value means the amplitude will decrease faster
	 * 0.25 will probably be a decent value
	 */
	virtual void setH(float H){this->H = H; initExponents();}
	virtual float getH() const {return H;}
private:
	void initExponents();
	Continuous2DSignal* baseNoise;
	unsigned int octaves;
	float lacunarity;
	float offset;
	float H;
	std::vector<float> exponents;
};

} // namespace ptg
#endif // RIDGEDMULTIFRACTAL_HPP
