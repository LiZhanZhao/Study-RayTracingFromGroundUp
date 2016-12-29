#include "Dielectric.h"


Dielectric::Dielectric(void)
: Phong(),
fresnel_reflector_brdf(new FresnelReflector),
fresnel_transmitter_btdf(new FresnelTransmitter)
{}


// ---------------------------------------------------------------- copy constructor

Dielectric::Dielectric(const Dielectric& rm)
: Phong(rm) {

	if (rm.fresnel_reflector_brdf)
		fresnel_reflector_brdf = rm.fresnel_reflector_brdf->clone();
	else
		fresnel_reflector_brdf = NULL;

	if (rm.fresnel_transmitter_btdf)
		fresnel_transmitter_btdf = rm.fresnel_transmitter_btdf->clone();
	else
		fresnel_transmitter_btdf = NULL;
}


// ---------------------------------------------------------------- assignment operator

Dielectric&
Dielectric::operator= (const Dielectric& rhs) {
	if (this == &rhs)
		return (*this);

	Phong::operator=(rhs);

	if (fresnel_reflector_brdf) {
		delete fresnel_reflector_brdf;
		fresnel_reflector_brdf = NULL;
	}

	if (rhs.fresnel_reflector_brdf)
		fresnel_reflector_brdf = rhs.fresnel_reflector_brdf->clone();


	if (fresnel_transmitter_btdf){
		delete fresnel_transmitter_btdf;
		fresnel_transmitter_btdf = NULL;
	}

	if (rhs.fresnel_transmitter_btdf)
		fresnel_transmitter_btdf = rhs.fresnel_transmitter_btdf->clone();

	return (*this);
}


// ---------------------------------------------------------------- clone

Dielectric*
Dielectric::clone(void) const {
	return (new Dielectric(*this));
}


// ---------------------------------------------------------------- destructor

Dielectric::~Dielectric(void) {
	if (fresnel_reflector_brdf) {
		delete fresnel_reflector_brdf;
		fresnel_reflector_brdf = NULL;
	}

	if (fresnel_transmitter_btdf){
		delete fresnel_transmitter_btdf;
		fresnel_transmitter_btdf = NULL;
	}
}


RGBColor
Dielectric::shade(ShadeRec& sr) {
	RGBColor L(Phong::shade(sr));

	Vector3D 	wi;
	Vector3D 	wo(-sr.ray.d);
	RGBColor 	fr = fresnel_reflector_brdf->sample_f(sr, wo, wi);  	// computes wi
	Ray 		reflected_ray(sr.hit_point, wi);
	double 		t = 0;
	RGBColor 	Lr, Lt;
	float 		ndotwi = sr.normal * wi;

	if (fresnel_transmitter_btdf->tir(sr)) {								// total internal reflection
		if (ndotwi < 0.0) {
			// reflected ray is inside

			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			L += cf_in.powc(t) * Lr;   						// inside filter color
		}
		else {
			// reflected ray is outside

			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);   // kr = 1  
			L += cf_out.powc(t) * Lr;   					// outside filter color
		}
	}
	else { 													// no total internal reflection
		Vector3D wt;
		RGBColor ft = fresnel_transmitter_btdf->sample_f(sr, wo, wt);  	// computes wt
		Ray transmitted_ray(sr.hit_point, wt);
		float ndotwt = sr.normal * wt;

		if (ndotwi < 0.0) {
			// reflected ray is inside

			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi);
			L += cf_in.powc(t) * Lr;     					// inside filter color

			// transmitted ray is outside

			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt);
			L += cf_out.powc(t) * Lt;   					// outside filter color
		}
		else {
			// reflected ray is outside

			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi);
			L += cf_out.powc(t) * Lr;						// outside filter color

			// transmitted ray is inside

			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt);
			L += cf_in.powc(t) * Lt; 						// inside filter color
		}
	}

	return (L);
}


void Dielectric::set_eta_in(float value){
	fresnel_reflector_brdf->set_eta_in(value);
	fresnel_transmitter_btdf->set_eta_in(value);
}

void Dielectric::set_eta_out(float value){
	fresnel_reflector_brdf->set_eta_out(value);
	fresnel_transmitter_btdf->set_eta_out(value);
}