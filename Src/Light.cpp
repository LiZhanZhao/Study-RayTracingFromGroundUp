// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Light.h"

#include "Constants.h"

// ---------------------------------------------------------------------- default constructor

Light::Light(void) {
	shadows = true;
}

// ---------------------------------------------------------------------- copy constructor

Light::Light(const Light& ls) : shadows(ls.shadows)
{}


// ---------------------------------------------------------------------- assignment operator

Light& 
Light::operator= (const Light& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------------- destructor

Light::~Light(void) {} 



// ---------------------------------------------------------------------- L
// returns the radiance

RGBColor Light::L(ShadeRec& s) {
	return (black);
}

bool Light::in_shadow(const Ray& ray, const ShadeRec& sr) const{
	return false;
}



