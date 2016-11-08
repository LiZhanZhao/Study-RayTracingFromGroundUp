#ifndef __PHONG__
#define __PHONG__

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

class Phong : public Material {
	public:

		Phong(void);

		Phong(const Phong& m);

		virtual Material* clone(void) const;

		Phong& operator= (const Phong& rhs);

		~Phong(void);

		virtual RGBColor shade(ShadeRec& sr);

	private:

		Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;
		GlossySpecular*	specular_brdf;

};



#endif