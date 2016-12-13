#ifndef __EMISSIVE__
#define __EMISSIVE__

#include "Material.h"
#include "Lambertian.h"


class Emissive : public Material {
private:

	float		ls;		// radiance scaling factor						 
	RGBColor 	ce;		// color

public:

	// constructors, set functions, etc ...
	Emissive(void);

	Emissive(const Emissive& m);

	virtual Material* clone(void) const;

	Emissive& operator= (const Emissive& rhs);

	~Emissive(void);

	void scale_radiance(const float _ls);

	void set_ce(const RGBColor c);

	void set_ce(const float r, const float g, const float b);

	virtual RGBColor get_Le(ShadeRec& sr) const;

	virtual RGBColor shade(ShadeRec& sr);

	virtual RGBColor area_light_shade(ShadeRec& sr);

	virtual RGBColor path_shade(ShadeRec& sr);
};

inline void Emissive::scale_radiance(const float _ls){
	ls = _ls;
}

inline void Emissive::set_ce(const float r, const float g, const float b){
	ce.r = r;
	ce.g = g;
	ce.b = b;
}

inline void Emissive::set_ce(const RGBColor c){
	ce = c;

}

#endif