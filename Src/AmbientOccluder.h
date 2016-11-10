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

		void scale_radiance(const float b);

		void set_color(const float c);

		void set_color(const RGBColor& c);

		void set_color(const float r, const float g, const float b);

		void set_min_amount(const float amount);

	private:

		float		ls;
		RGBColor	color;
		float 		min_amount;
		Vector3D 	u, v, w;
		Sampler*	sampler_ptr;
};

inline void
AmbientOccluder::scale_radiance(const float b) {
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
AmbientOccluder::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
AmbientOccluder::set_color(const RGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
AmbientOccluder::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

inline void AmbientOccluder::set_min_amount(const float amount){
	min_amount = amount;
}

#endif