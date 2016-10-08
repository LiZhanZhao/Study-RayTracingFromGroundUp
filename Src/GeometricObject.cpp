// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// this file contains the definition of the class GeometricObject 

#include "Constants.h"
#include "GeometricObject.h"


// ---------------------------------------------------------------------- default constructor

GeometricObject::GeometricObject(void)
	: 	color(black)
{}


// ---------------------------------------------------------------------- copy constructor

GeometricObject::GeometricObject (const GeometricObject& object)
	: 	color(object.color)
{
}	


// ---------------------------------------------------------------------- destructor

GeometricObject::~GeometricObject (void) {	
	
}
									

