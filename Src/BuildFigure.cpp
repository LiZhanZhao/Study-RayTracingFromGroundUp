// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Pinhole.h"
#include "ThinLens.h"

void
World::build(void) {
	vp.set_hres(200);
	vp.set_vres(200);
	buffer = new RGBColor[vp.vres * vp.hres];

	int num_samples = 16;
	vp.set_sampler(new MultiJittered(num_samples));

	ThinLens* thin_lens_ptr = new ThinLens;
	thin_lens_ptr->set_sampler(new MultiJittered(num_samples));
	thin_lens_ptr->set_eye(20, 0, 30);
	thin_lens_ptr->set_lookat(0, 0, 0);
	thin_lens_ptr->set_view_distance(50.0);
	thin_lens_ptr->set_focal_distance(20.0);
	thin_lens_ptr->set_lens_radius(3.0);     
	thin_lens_ptr->compute_uvw();
	set_camera(thin_lens_ptr);

	/*Pinhole* pinhole_ptr = new Pinhole();
	pinhole_ptr->set_eye(0, 0, -90);
	pinhole_ptr->set_lookat(0, 0, 0);
	pinhole_ptr->set_view_distance(10);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);*/

	background_color = black;
	tracer_ptr = new MultipleObjects(this);

	// use access functions to set center and radius for this sphere

	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(0, 0, 0);
	sphere_ptr->set_radius(20.0);
	sphere_ptr->set_color(1, 0, 0);  // red
	add_object(sphere_ptr);

	// use a constructor to set center and radius for this sphere

	
	sphere_ptr = new Sphere();
	sphere_ptr->set_center(0, 0, -80);
	sphere_ptr->set_radius(80.0f);
	sphere_ptr->set_color(1, 1, 0);	// yellow
	add_object(sphere_ptr);


	//Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 1));
	//plane_ptr->set_color(0.0, 0.25, 0.0);	// dark green 
	//add_object(plane_ptr);
}


