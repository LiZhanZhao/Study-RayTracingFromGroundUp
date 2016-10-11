// This file contains the definition the ViewPlane class

#include "ViewPlane.h"
	
// ---------------------------------------------------------------- default constructor	
						
ViewPlane::ViewPlane(void)							
	: 	hres(400), 
		vres(400),
		s(1.0),
		num_samples(1),
		gamma(1.0),
		inv_gamma(1.0),
		show_out_of_gamut(false),
		sampler_ptr(NULL)
{}


// ---------------------------------------------------------------- copy constructor

ViewPlane::ViewPlane(const ViewPlane& vp)   
	:  	hres(vp.hres),  
		vres(vp.vres), 
		s(vp.s),
		num_samples(vp.num_samples),
		gamma(vp.gamma),
		inv_gamma(vp.inv_gamma),
		show_out_of_gamut(vp.show_out_of_gamut),
		sampler_ptr(vp.sampler_ptr)
{}


// ---------------------------------------------------------------- assignment operator

ViewPlane& 
ViewPlane::operator= (const ViewPlane& rhs) {
	if (this == &rhs)
		return (*this);
		
	hres 				= rhs.hres;
	vres 				= rhs.vres;
	s					= rhs.s;
	num_samples			= rhs.num_samples;
	gamma				= rhs.gamma;
	inv_gamma			= rhs.inv_gamma;
	show_out_of_gamut	= rhs.show_out_of_gamut;
	sampler_ptr = rhs.sampler_ptr;
	return (*this);
}


// -------------------------------------------------------------- destructor

ViewPlane::~ViewPlane(void) {}



void ViewPlane::set_sampler(Sampler* sp)
{
	if (sampler_ptr != NULL){
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	num_samples = sp->get_num_samples();
	sampler_ptr = sp;
	
}


	





