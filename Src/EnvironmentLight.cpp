#include "EnvironmentLight.h"

EnvironmentLight::EnvironmentLight(void)
: Light(), sampler_ptr(NULL), material_ptr(NULL)
{}

EnvironmentLight::EnvironmentLight(const EnvironmentLight& al)
: Light(al) {
	if (al.sampler_ptr)
		sampler_ptr = al.sampler_ptr->clone();
	else  sampler_ptr = NULL;

	if (al.material_ptr)
		material_ptr = al.material_ptr->clone();
	else  material_ptr = NULL;
}

Light* EnvironmentLight::clone(void) const{
	return (new EnvironmentLight(*this));
}

EnvironmentLight::~EnvironmentLight(void) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}


EnvironmentLight& EnvironmentLight::operator = (const EnvironmentLight& rhs){
	if (this == &rhs)
		return (*this);

	Light::operator=(rhs);

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();

	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();

	return (*this);
}

void EnvironmentLight::set_sampler(Sampler* s_ptr){
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);

}

void EnvironmentLight::set_material(Material* mat_ptr){
	if (material_ptr != NULL){
		delete material_ptr;
		material_ptr = NULL;
	}
	material_ptr = mat_ptr;
}


Vector3D EnvironmentLight::get_direction(ShadeRec& sr) {
	w = sr.normal;
	v = w ^ Vector3D(0.0072, 1.0, 0.0034); // jitter the up vector in case normal is vertical
	v.normalize();
	u = v ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;

	return (wi);
}

RGBColor EnvironmentLight::L(ShadeRec& sr) {
	return (material_ptr->get_Le(sr));
}

float EnvironmentLight::pdf(const ShadeRec& sr) const{
	return (sr.normal * wi * invPI);
}

bool EnvironmentLight::in_shadow(const Ray& ray, const ShadeRec& sr) const{
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

