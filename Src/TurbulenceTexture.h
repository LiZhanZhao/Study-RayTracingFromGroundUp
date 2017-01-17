#ifndef __TURBULENCE_TEXTURE__
#define __TURBULENCE_TEXTURE__

#include "Texture.h"
#include "Constants.h"
#include "LatticeNoise.h"

class TurbulenceTexture : public Texture {
public:

	// constructors etc ...
	TurbulenceTexture(LatticeNoise* texture);

	TurbulenceTexture(const TurbulenceTexture& texture);

	virtual TurbulenceTexture*
		clone(void) const;

	virtual ~TurbulenceTexture(void);

	TurbulenceTexture& operator= (const TurbulenceTexture& rhs);

	virtual RGBColor
		get_color(const ShadeRec& sr) const;

	void set_color(float r, float g, float b);

	void set_min_value(float min);

	void set_max_value(float max);


private:

	LatticeNoise*		noise_ptr;
	RGBColor 	  		color;
	float		  		min_value, max_value;	// scaling factors
};


inline void TurbulenceTexture::set_color(float r, float g, float b){
	color = RGBColor(r, g, b);
}

inline void TurbulenceTexture::set_min_value(float min){
	min_value = min;
}

inline void TurbulenceTexture::set_max_value(float max){
	max_value = max;
}

#endif