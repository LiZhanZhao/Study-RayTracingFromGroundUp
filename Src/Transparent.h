#ifndef __TRANSPARENT__
#define __TRANSPARENT__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Phong.h"
#include "PerfectSpecular.h"
#include "PerfectTransmitter.h"

class Transparent: public Phong {	
	public:
	
		Transparent(void);

		Transparent(const Transparent& rm);

		Transparent&
			operator= (const Transparent& rhs);

		virtual Transparent*
		clone(void) const;				

		~Transparent(void);
		
		void
		set_kr(const float k);
				
		void													
		set_cr(const RGBColor& c);
		
		void
		set_cr(const float r, const float g, const float b);
		
		void
		set_cr(const float c);

		void set_ior(const float eta);

		void set_kt(const float k);
		
		virtual RGBColor shade(ShadeRec& s);

		//virtual RGBColor area_light_shade(ShadeRec& sr);

		//virtual RGBColor path_shade(ShadeRec& sr);

		//virtual RGBColor global_shade(ShadeRec& sr);
		
	private:
	
		PerfectSpecular* reflective_brdf;
		PerfectTransmitter* specular_btdf;
};


// ---------------------------------------------------------------- set_kr

inline void
Transparent::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}


// ---------------------------------------------------------------- set_cr

inline void
Transparent::set_cr(const RGBColor& c) {
	reflective_brdf->set_cr(c);
	
}


// ---------------------------------------------------------------- set_cr

inline void
Transparent::set_cr(const float r, const float g, const float b) {
	reflective_brdf->set_cr(r, g, b);
}


// ---------------------------------------------------------------- set_cr

inline void
Transparent::set_cr(const float c) {
	reflective_brdf->set_cr(c);
}

inline void Transparent::set_ior(const float eta){
	specular_btdf->set_ior(eta);
}

inline void Transparent::set_kt(const float k){
	specular_btdf->set_kt(k);
}

#endif
