#ifndef __WRAPPED_FBM_TEXTURE__
#define __WRAPPED_FBM_TEXTURE__

#include "Texture.h"
#include "Constants.h"
#include "LatticeNoise.h"

class WrappedFBmTexture : public Texture {
public:

	// constructors etc ...
	WrappedFBmTexture(LatticeNoise* texture);

	WrappedFBmTexture(const WrappedFBmTexture& texture);

	virtual WrappedFBmTexture*
		clone(void) const;

	virtual ~WrappedFBmTexture(void);

	WrappedFBmTexture& operator= (const WrappedFBmTexture& rhs);

	virtual RGBColor
		get_color(const ShadeRec& sr) const;

	void set_color(float r, float g, float b);

	void set_min_value(float min);

	void set_max_value(float max);

	void set_expansion_number(float value);

private:

	LatticeNoise*		noise_ptr;
	RGBColor 	  		color;
	float		  		min_value, max_value;	// scaling factors
	float expansion_number;
};


inline void WrappedFBmTexture::set_color(float r, float g, float b){
	color = RGBColor(r, g, b);
}

inline void WrappedFBmTexture::set_min_value(float min){
	min_value = min;
}

inline void WrappedFBmTexture::set_max_value(float max){
	max_value = max;
}

inline void WrappedFBmTexture::set_expansion_number(float value){
	expansion_number = value;
}

#endif