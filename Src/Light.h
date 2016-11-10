#ifndef __LIGHT__
#define __LIGHT__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Vector3D.h"
#include "RGBColor.h"
#include "Ray.h"

class ShadeRec;


//-------------------------------------------------------------------- class Light

class Light {	
	public:
	
		Light(void);
								
		Light(const Light& ls);			

		Light& 								
		operator= (const Light& rhs); 

		virtual Light* 						
		clone(void) const = 0;
		
		virtual 							
		~Light(void);
						
		virtual Vector3D								
		get_direction(ShadeRec& sr) = 0;				
																
		virtual RGBColor L(ShadeRec& sr);

		void set_shadows(bool isOpen);

		bool casts_shadows();

		virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

		virtual float G(const ShadeRec& sr) const;

		virtual float pdf(const ShadeRec& sr) const;

	protected:
		bool shadows;

};

inline void Light::set_shadows(bool isOpen){
	shadows = isOpen;
}

inline bool Light::casts_shadows(){
	return shadows;
}

#endif
