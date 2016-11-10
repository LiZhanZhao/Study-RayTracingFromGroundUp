#include"AmbientOccluder.h"

AmbientOccluder::AmbientOccluder(void)
: Light(), ls(1.0), color(1.0), min_amount(1.0)
{
	u = Vector3D(1, 0, 0);
	v = Vector3D(0, 1, 0);
	w = Vector3D(0, 0, 1);
	sampler_ptr = NULL;
}

AmbientOccluder::AmbientOccluder(const AmbientOccluder& dl)
: Light(dl), ls(dl.ls), color(dl.color), min_amount(dl.min_amount)
{
	u = dl.u;
	v = dl.v;
	w = dl.w;
	sampler_ptr = dl.sampler_ptr;
}

Light* AmbientOccluder::clone(void) const{
	return (new AmbientOccluder(*this));
}

AmbientOccluder& AmbientOccluder::operator= (const AmbientOccluder& rhs){
	if (this == &rhs)
		return (*this);

	Light::operator= (rhs);

	ls = rhs.ls;
	color = rhs.color;
	u = rhs.u;
	v = rhs.v;
	w = rhs.w;
	sampler_ptr = rhs.sampler_ptr;
	min_amount = rhs.min_amount;

	return (*this);
}

AmbientOccluder::~AmbientOccluder(void){ }

void AmbientOccluder::set_sampler(Sampler* s_ptr){
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);

}

Vector3D AmbientOccluder::get_direction(ShadeRec& sr){
	Point3D sp = sampler_ptr->sample_hemisphere();
	return (sp.x * u + sp.y * v + sp.z * w);
}

bool AmbientOccluder::in_shadow(const Ray& ray, const ShadeRec& sr) const{
	float 	t;
	int 	num_objects = sr.w.objects.size();
	for (int j = 0; j < num_objects; j++)
	{
		if (sr.w.objects[j]->shadow_hit(ray, t))
		{
			return (true);
		}
	}
	return (false);

}

RGBColor AmbientOccluder::L(ShadeRec& sr){
	w = sr.normal;
	v = w ^ Vector3D(0.0072, 1.0, 0.0034); // jitter the up vector in case normal is vertical
	v.normalize();
	u = v ^ w;

	Ray shadow_ray;
	shadow_ray.o = sr.hit_point;
	// use sampler to determine sahdow ray 's direction
	shadow_ray.d = get_direction(sr);

	if (in_shadow(shadow_ray, sr))
		return (min_amount * ls * color);
	else
		return (ls * color);
}