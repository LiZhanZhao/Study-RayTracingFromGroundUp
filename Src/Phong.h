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

		void set_ka(const float k);

		void set_kd(const float k);

		void set_cd(const RGBColor c);

		void set_cd(const float r, const float g, const float b);

		void set_cd(const float c);

		void set_ks(const float k);

		void set_exp(const float exp);

	private:

		Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;
		GlossySpecular*	specular_brdf;

};

inline void Phong::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}

inline void Phong::set_kd(const float kd) {
	diffuse_brdf->set_kd(kd);
}

inline void Phong::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void Phong::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

inline void Phong::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void Phong::set_ks(const float k){
	specular_brdf->set_ks(k);
}

inline void Phong::set_exp(const float exp){
	specular_brdf->set_exp(exp);
}

#endif