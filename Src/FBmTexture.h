#ifndef __FBM_TEXTURE__
#define __FBM_TEXTURE__

#include "Texture.h"
#include "Constants.h"
#include "LatticeNoise.h"

class FBmTexture : public Texture {
public:

	// constructors etc ...
	FBmTexture(LatticeNoise* texture);

	FBmTexture(const FBmTexture& texture);

	virtual FBmTexture*
		clone(void) const;

	virtual ~FBmTexture(void);

	FBmTexture& operator= (const FBmTexture& rhs);

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


inline void FBmTexture::set_color(float r, float g, float b){
	color = RGBColor(r, g, b);
}

inline void FBmTexture::set_min_value(float min){
	min_value = min;
}

inline void FBmTexture::set_max_value(float max){
	max_value = max;
}

#endif