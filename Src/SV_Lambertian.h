#ifndef __SV_LAMBERTIAN__
#define __SV_LAMBERTIAN__

#include "BRDF.h"
#include "Texture.h"

class SV_Lambertian : public BRDF {
public:

	// constructors, etc ...
	SV_Lambertian(void);

	SV_Lambertian(const SV_Lambertian& lamb);

	SV_Lambertian& operator= (const SV_Lambertian& rhs);

	void set_cd(Texture* tex);

	void set_kd(const float value);

	virtual ~SV_Lambertian(void);

	virtual SV_Lambertian* clone(void) const;

	virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;

	virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

private:

	float		kd;
	Texture*    cd;
};

inline void SV_Lambertian::set_kd(const float value){
	kd = value;
}



#endif