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

	private:

		RGBColor 			cf_in;			// interior filter color 
		RGBColor 			cf_out;			// exterior filter color

		FresnelReflector*	fresnel_reflector_brdf;
		FresnelTransmitter*	fresnel_transmitter_btdf;
};

inline void Dielectric::set_ior(const float eta){
	fresnel_transmitter_btdf->set_ior(eta);
}





#endif