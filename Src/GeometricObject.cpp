// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// this file contains the definition of the class GeometricObject 

#include "Constants.h"
#include "GeometricObject.h"


// ---------------------------------------------------------------------- default constructor

GeometricObject::GeometricObject(void)
: color(black), material_ptr(NULL)
{}


// ---------------------------------------------------------------------- copy constructor

GeometricObject::GeometricObject(const GeometricObject& object)
: color(object.color), material_ptr(object.material_ptr)
{
}	


// ---------------------------------------------------------------------- destructor

GeometricObject::~GeometricObject (void) {	
	if (material_ptr != NULL){
		delete material_ptr;
		material_ptr = NULL;
	}
}
void GeometricObject::set_material(Material* mPtr){
	material_ptr = mPtr;
}

Material* GeometricObject::get_material(void){
	return material_ptr;
}

bool GeometricObject::shadow_hit(const Ray& ray, float& t) const{
	return false;
}
