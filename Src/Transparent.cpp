// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Transparent.h"

// ---------------------------------------------------------------- default constructor

Transparent::Transparent(void)
	:	Phong(),
		reflective_brdf(new PerfectSpecular),
		specular_btdf(new PerfectTransmitter)
{}


// ---------------------------------------------------------------- copy constructor

Transparent::Transparent(const Transparent& rm)
	: 	Phong(rm) {
	
	if(rm.reflective_brdf)
		reflective_brdf = rm.reflective_brdf->clone(); 
	else  
		reflective_brdf = NULL;

	if (rm.specular_btdf)
		specular_btdf = rm.specular_btdf->clone();
	else
		specular_btdf = NULL;
}


// ---------------------------------------------------------------- assignment operator

Transparent&
Transparent::operator= (const Transparent& rhs) {
	if (this == &rhs)
		return (*this);
		
	Phong::operator=(rhs);
	
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}

	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();


	if (specular_btdf){
		delete specular_btdf;
		specular_btdf = NULL;
	}

	if (rhs.specular_btdf)
		specular_btdf = rhs.specular_btdf->clone();

	return (*this);
}


// ---------------------------------------------------------------- clone

Transparent*
Transparent::clone(void) const {
	return (new Transparent(*this));
}	


// ---------------------------------------------------------------- destructor

Transparent::~Transparent(void) {
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}

	if (specular_btdf){
		delete specular_btdf;
		specular_btdf = NULL;
	}
}


// ------------------------------------------------------------------------------------ shade 

RGBColor
Transparent::shade(ShadeRec& sr) {
	RGBColor L(Phong::shade(sr));  // direct illumination
	
	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	// sample_f calculate wi 
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi); 
	Ray reflected_ray(sr.hit_point, wi); 
	

	// because fr = (kr * cr / fabs(sr.normal * wi)), so this is equal 
	// L += kr * cr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)
	//L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);
	
	if (specular_btdf->tir(sr)){
		// kr = 1.0
		L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
	}
	else{
		Vector3D wt;
		RGBColor ft = specular_btdf->sample_f(sr, wo, wt);
		Ray transmitted_ray(sr.hit_point, wt);
		
		L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * fabs(sr.normal * wi);

		L += ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1) * fabs(sr.normal * wt);
	}


	return (L);
}

/*
RGBColor Transparent::area_light_shade(ShadeRec& sr){
	RGBColor 	L(Phong::area_light_shade(sr));  // direct illumination

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	// sample_f calculate wi 
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
	Ray reflected_ray(sr.hit_point, wi);
	//reflected_ray.depth = sr.depth + 1;

	// because fr = (kr * cr / fabs(sr.normal * wi)), so this is equal 
	// L += kr * cr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)
	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);

	return (L);
}

RGBColor Transparent::path_shade(ShadeRec& sr){
	Vector3D 	wo = -sr.ray.d;
	Vector3D 	wi;
	float 		pdf;
	RGBColor 	fr = reflective_brdf->sample_f(sr, wo, wi, pdf);
	Ray 		reflected_ray(sr.hit_point, wi);

	return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
}

RGBColor Transparent::global_shade(ShadeRec& sr){
	Vector3D 	wo = -sr.ray.d;
	Vector3D 	wi;
	float 		pdf;
	RGBColor 	fr = reflective_brdf->sample_f(sr, wo, wi, pdf);
	Ray 		reflected_ray(sr.hit_point, wi);

	if (sr.depth == 0)
		return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 2) * (sr.normal * wi) / pdf);
	else
		return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
}
*/