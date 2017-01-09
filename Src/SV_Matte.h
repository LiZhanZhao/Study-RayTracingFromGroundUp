#ifndef __SV_MATTE__
#define __SV_MATTE__

#include "Material.h"
#include "SV_Lambertian.h"

class SV_Matte : public Material {
public:

	// consructors, etc ...
	SV_Matte(void);

	SV_Matte(const SV_Matte& m);

	virtual Material*
		clone(void) const;

	SV_Matte& operator= (const SV_Matte& rhs);

	~SV_Matte(void);

	void
		set_cd(Texture* t_ptr);

	virtual RGBColor
		shade(ShadeRec& s);

private:

	SV_Lambertian*	ambient_brdf;
	SV_Lambertian*	diffuse_brdf;
};


inline void
SV_Matte::set_cd(Texture* t_ptr) {
	ambient_brdf->set_cd(t_ptr);
	diffuse_brdf->set_cd(t_ptr);
}



#endif
