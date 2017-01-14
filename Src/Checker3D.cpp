#include "Checker3D.h"

Checker3D::Checker3D(void)
: Texture(), size(1.0f), color1(1.0f, 1.0f, 1.0f), color2(1.0f, 1.0f, 1.0f)
{}

Checker3D::Checker3D(const Checker3D& it)
: Texture(it), size(it.size), color1(it.color1), color2(it.color2)
{
}

Checker3D* Checker3D::clone(void) const{
	return (new Checker3D(*this));
}

Checker3D::~Checker3D(void){
}

Checker3D&
Checker3D::operator= (const Checker3D& rhs){
	if (this == &rhs)
		return (*this);

	Texture::operator= (rhs);
	return (*this);
}


RGBColor
Checker3D::get_color(const ShadeRec& sr) const {

	float eps = -0.000187453738;	// small random number
	float x = sr.local_hit_point.x + eps;
	float y = sr.local_hit_point.y + eps;
	float z = sr.local_hit_point.z + eps;

	if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / size)) % 2 == 0)
		return (color1);
	else
		return (color2);
}
