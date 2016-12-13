#include "Emissive.h"

Emissive::Emissive(void) : Material(), ls(1), ce(1.0)
{}

Emissive::Emissive(const Emissive& m) : Material(m), ls(m.ls), ce(m.ce)
{}

Material* Emissive::clone(void) const {
	return (new Emissive(*this));
}

Emissive& Emissive::operator= (const Emissive& rhs){
	if (this == &rhs)
		return (*this);

	Material::operator=(rhs);
	ls = rhs.ls;
	ce = rhs.ce;
	return (*this);
}

Emissive::~Emissive(void){}

RGBColor Emissive::area_light_shade(ShadeRec& sr) {
	// when the incoming ray is on the same side of the object surface as the normal
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return (black);
}

RGBColor Emissive::shade(ShadeRec& sr){
	// when the incoming ray is on the same side of the object surface as the normal
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return (black);
}

RGBColor Emissive::get_Le(ShadeRec& sr) const{
	return ls * ce;
}

RGBColor Emissive::path_shade(ShadeRec& sr){
	/*
	// when the incoming ray is on the same side of the object surface as the normal
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return (black);
	*/

	// As long as hit emissive object then return
	return (ls * ce);
}