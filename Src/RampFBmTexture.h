#ifndef __RAMP_FBM_TEXTURE__
#define __RAMP_FBM_TEXTURE__

#include "Texture.h"
#include "Constants.h"
#include "LatticeNoise.h"
#include "Image.h"

class RampFBmTexture : public Texture {
public:

	// constructors etc ...
	RampFBmTexture(Image* image);

	RampFBmTexture(const RampFBmTexture& texture);

	virtual RampFBmTexture*
		clone(void) const;

	virtual ~RampFBmTexture(void);

	RampFBmTexture& operator= (const RampFBmTexture& rhs);

	virtual RGBColor
		get_color(const ShadeRec& sr) const;

	void set_noise(LatticeNoise* noise);
	void set_perturbation(float value);

private:
	Image*				ramp_ptr;			// this stores the ramp image	
	LatticeNoise*  		noise_ptr;			// supplies the value_fbm noise function
	float				perturbation;		// the amount of fbm ("a" in the book)
};

inline void RampFBmTexture::set_noise(LatticeNoise* noise){
	noise_ptr = noise;
}

inline void RampFBmTexture::set_perturbation(float value){
	perturbation = value;

}

#endif