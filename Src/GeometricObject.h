#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <math.h>  // a lot of hit functions use use maths functions

#include "Constants.h"
#include "RGBColor.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Normal.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Sampler.h"

class Material;	


//----------------------------------------------------------------------------------------------------- class GeometricObject

class GeometricObject {	
	public:	

		GeometricObject(void);									
		
		GeometricObject(const GeometricObject& object);			
	
		virtual GeometricObject*								
		clone(void) const = 0;

		virtual 												
		~GeometricObject(void);	
			
		virtual bool 												 
		hit(const Ray& ray, double& t, ShadeRec& s) const = 0;	
		
		// The following three functions are only required for Chapter 3

		void
		set_color(const RGBColor& c);
				
		void
		set_color(const float r, const float g, const float b);
		
		RGBColor
		get_color(void);

		void set_material(Material* mPtr);

		Material* get_material(void);

		virtual bool shadow_hit(const Ray& ray, float& t) const;

		/*void set_shadows(bool isOpen);*/

		virtual void set_sampler(Sampler* sampler);

		virtual Point3D sample(void);

		virtual Normal get_normal(const Point3D& p);

		virtual float pdf(const ShadeRec& sr);

	protected:
		RGBColor color;				// only used for Bare Bones ray tracing
		Material* material_ptr;
		//bool shadows;

		//Sampler* sampler_ptr;
};


// --------------------------------------------------------------------  set_color

inline void
GeometricObject::set_color(const RGBColor& c) {
	color = c;
}

// --------------------------------------------------------------------  set_color

inline void 
GeometricObject::set_color(const float r, const float g, const float b) {
	color.r = r;
	color.b = b;
	color.g = g;
}

// --------------------------------------------------------------------  get_color

inline RGBColor GeometricObject::get_color(void) {
	return (color);
}

//inline void GeometricObject::set_shadows(bool isOpen){
//	shadows = isOpen;
//}


#endif
