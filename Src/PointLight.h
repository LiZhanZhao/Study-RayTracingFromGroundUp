#ifndef __POINTLIGHT__
#define __POINTLIGHT__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Light.h"
#include "Vector3D.h"
#include "RGBColor.h"

#include "World.h"			// you will need this later on for shadows
#include "ShadeRec.h"


class PointLight: public Light {
	public:
	
		PointLight(void);

		PointLight(const PointLight& dl);
		
		virtual Light* 									
		clone(void) const;			

		PointLight& operator= (const PointLight& rhs);
			
		virtual ~PointLight(void);
				
		void
		scale_radiance(const float b);
		
		void
		set_color(const float c);
		
		void
		set_color(const RGBColor& c);
		
		void
		set_color(const float r, const float g, const float b); 		
			
		void set_location(Vector3D pos);
		
		void set_location(float px, float py, float pz);
		
		virtual Vector3D								
		get_direction(ShadeRec& sr);
				
		virtual RGBColor		
		L(ShadeRec& sr);	
		
	private:

		float		ls;			
		RGBColor	color;
		Vector3D 	location;
};


// inlined access functions


// ------------------------------------------------------------------------------- scale_radiance

inline void
PointLight::scale_radiance(const float b) {
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const RGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

inline void PointLight::set_location(Vector3D pos){
	location = pos;
}

inline void PointLight::set_location(float px, float py, float pz){
	location.x = px;
	location.y = py;
	location.z = pz;
}

#endif

