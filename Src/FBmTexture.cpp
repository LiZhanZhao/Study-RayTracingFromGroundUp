#include "FBmTexture.h"

FBmTexture::FBmTexture(LatticeNoise* texture)
: Texture(), noise_ptr(texture), color(1.0f, 1.0f, 1.0f), min_value(0.0f), max_value(1.0f)
{

}

FBmTexture::FBmTexture(const FBmTexture& texture)
: Texture(texture), noise_ptr(texture.noise_ptr), color(texture.color), min_value(texture.min_value),
max_value(texture.max_value)
{

}


FBmTexture* FBmTexture::clone(void) const{
	return (new FBmTexture(*this));
}

FBmTexture::~FBmTexture(void){
}

FBmTexture&
FBmTexture::operator= (const FBmTexture& rhs){
	if (this == &rhs)
		return (*this);

	Texture::operator= (rhs);

	if (noise_ptr != NULL){
		delete noise_ptr;
		noise_ptr = NULL;
	}
	noise_ptr = rhs.noise_ptr;
	color = rhs.color;
	min_value = rhs.min_value;
	max_value = rhs.max_value;

	return (*this);
}

RGBColor
FBmTexture::get_color(const ShadeRec& sr) const {

	float value = noise_ptr->value_fbm(sr.local_hit_point); // in the range (0, 1)
	value = min_value + (max_value - min_value) * value;	// in the range (min_value, max_value)

	return (value * color);
}