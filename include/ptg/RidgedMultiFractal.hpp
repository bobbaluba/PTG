/**
 * @file HybridMultiFractal.hpp
 * @date 12. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef RIDGEDMULTIFRACTAL_HPP
#define RIDGEDMULTIFRACTAL_HPP

#include <ptg/Continuous2DSignal.hpp>

#include <vector>

namespace ptg {

/** @brief Fractal noise generated using ridged multi fractal as described by
 * Musgrave
 */
class RidgedMultiFractal: public ptg::Continuous2DSignal {
public:
	explicit RidgedMultiFractal(unsigned int seed=0);
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

	/** @brief sets the offset.
	 *
	 * this offset is different from that of hybrid multi fractal
	 * noise is subtracted from this noise before squaring, so having
	 * a value close to 1 is important.
	 *
	 * 1 will probably be a decent value
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

	virtual void setThreshold(float threshold){this->threshold=threshold;}
	virtual float getThreshold() const {return threshold;}

	RidgedMultiFractal(const RidgedMultiFractal&) = default;
	RidgedMultiFractal & operator=(const RidgedMultiFractal&) = default;
private:
	void initExponents();
	Continuous2DSignal* baseNoise;
	unsigned int octaves;
	float lacunarity;
	float offset;
	float H;
	float threshold;
	std::vector<float> exponents;
};

} // namespace ptg
#endif // RIDGEDMULTIFRACTAL_HPP
