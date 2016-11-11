#ifndef __ENVIRONMENT_LIGHT__
#define __ENVIRONMENT_LIGHT__

#include "RGBColor.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "Light.h"
#include "Material.h"
//#include "GeometricObject.h"

class EnvironmentLight : public Light {
	public:
		// constructors etc...

		EnvironmentLight(void);

		EnvironmentLight(const EnvironmentLight& al);

		virtual Light* clone(void) const;

		virtual ~EnvironmentLight(void);

		EnvironmentLight& operator= (const EnvironmentLight& rhs);

		void set_sampler(Sampler* sampler);

		virtual Vector3D get_direction(ShadeRec& s);

		virtual RGBColor L(ShadeRec& sr);

		virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

		virtual float pdf(const ShadeRec& sr) const;

		void set_material(Material* mat_ptr);

	private:
		Sampler*	sampler_ptr;
		Material* 	material_ptr;
		Vector3D	u, v, w;
		Vector3D	wi;
};

#endif
