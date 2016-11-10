#ifndef __AMBIENT_OCCLUDER__
#define __AMBIENT_OCCLUDER__

#include "Light.h"
#include "Vector3D.h"
#include "RGBColor.h"

#include "World.h"			// you will need this later on for shadows
#include "ShadeRec.h"

class AmbientOccluder : public Light {
	public:

		AmbientOccluder(void);

		AmbientOccluder(const AmbientOccluder& dl);

		virtual Light* clone(void) const;

		AmbientOccluder& operator= (const AmbientOccluder& rhs);

		virtual ~AmbientOccluder(void);
	
		void set_sampler(Sampler* s_ptr);

		virtual Vector3D get_direction(ShadeRec& sr);

		virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

		virtual RGBColor L(ShadeRec& sr);

	private:

		float		ls;
		RGBColor	color;
		float 		min_amount;
		Vector3D 	u, v, w;
		Sampler*	sampler_ptr;
};


#endif