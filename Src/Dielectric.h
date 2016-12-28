#ifndef __DIELECTRIC__
#define __DIELECTRIC__

#include "Phong.h"
#include "FresnelReflector.h"
#include "FresnelTransmitter.h"

class Dielectric : public Phong {
	public:

		Dielectric(void);

		Dielectric(const Dielectric& rm);

		Dielectric& operator= (const Dielectric& rhs);

		virtual Dielectric* clone(void) const;

		~Dielectric(void);


		virtual RGBColor shade(ShadeRec& s);

		void set_ior(const float eta);

		void set_eta_in(float value);

		void set_eta_out(float value);

		void set_cf_in(RGBColor color);

		void set_cf_out(RGBColor color);

	private:

		RGBColor 			cf_in;			// interior filter color 
		RGBColor 			cf_out;			// exterior filter color

		FresnelReflector*	fresnel_reflector_brdf;
		FresnelTransmitter*	fresnel_transmitter_btdf;
};

inline void Dielectric::set_cf_in(RGBColor color){
	cf_in = color;
}

inline void Dielectric::set_cf_out(RGBColor color){
	cf_out = color;
}





#endif