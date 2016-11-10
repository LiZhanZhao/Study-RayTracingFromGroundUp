// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Material.h"

// ---------------------------------------------------------------- default constructor

Material::Material(void)
:shadows(true)
{}


// ---------------------------------------------------------------- copy constructor

Material::Material(const Material& m)
: shadows(m.shadows)
{}



// ---------------------------------------------------------------- assignment operator

Material& 
Material::operator= (const Material& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------- destructor

Material::~Material(void)
{}


// ---------------------------------------------------------------- shade

RGBColor
Material::shade(ShadeRec& sr) {
	return (black);
}

void Material::set_shadows(bool isOpen){
	shadows = isOpen;
}

RGBColor Material::get_Le(ShadeRec& sr) const{
	return (black);
}

RGBColor Material::area_light_shade(ShadeRec& sr){
	return (black);
}


