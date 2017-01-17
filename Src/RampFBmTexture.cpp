#include "RampFBmTexture.h"

RampFBmTexture::RampFBmTexture(Image* image)
: Texture(), ramp_ptr(image), noise_ptr(NULL), perturbation(1.0f)
{

}

RampFBmTexture::RampFBmTexture(const RampFBmTexture& texture)
: Texture(texture), ramp_ptr(texture.ramp_ptr), noise_ptr(texture.noise_ptr),
perturbation(texture.perturbation)
{

}


RampFBmTexture* RampFBmTexture::clone(void) const{
	return (new RampFBmTexture(*this));
}

RampFBmTexture::~RampFBmTexture(void){
}

RampFBmTexture&
RampFBmTexture::operator= (const RampFBmTexture& rhs){
	if (this == &rhs)
		return (*this);

	Texture::operator= (rhs);

	if (ramp_ptr != NULL){
		delete ramp_ptr;
		ramp_ptr = NULL;
	}

	if (noise_ptr != NULL){
		delete noise_ptr;
		noise_ptr = NULL;
	}
	noise_ptr = rhs.noise_ptr;
	ramp_ptr = rhs.ramp_ptr;
	perturbation = rhs.perturbation;


	return (*this);
}

RGBColor
RampFBmTexture::get_color(const ShadeRec& sr) const {

	float 	noise = noise_ptr->value_fbm(sr.local_hit_point);
	float 	y = sr.local_hit_point.y + perturbation * noise;
	float 	u = (1.0 + sin(y)) / 2.0;
	int 	row = 0;    // use top row of ramp image
	int 	column = (int)(u * (ramp_ptr->get_hres() - 1));

	return (ramp_ptr->get_color(row, column));
}