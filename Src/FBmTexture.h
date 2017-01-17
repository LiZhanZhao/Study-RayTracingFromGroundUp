#ifndef __FBM_TEXTURE__
#define __FBM_TEXTURE__

#include "Texture.h"
#include "Constants.h"
#include "LatticeNoise.h"

class FBmTexture : public Texture {
public:

	// constructors etc ...
	FBmTexture(void);

	FBmTexture(const FBmTexture& texture);

	virtual FBmTexture*
		clone(void) const;

	virtual ~FBmTexture(void);

	FBmTexture& operator= (const FBmTexture& rhs);

	virtual RGBColor
		get_color(const ShadeRec& sr) const;

private:

	LatticeNoise*		noise_ptr;
	RGBColor 	  		color;
	float		  		min_value, max_value;	// scaling factors
};

#endif