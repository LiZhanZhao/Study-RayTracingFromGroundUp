// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.




#include "Matte.h"
#include "Phong.h"

void World::build(void) {

	// test Phong material and lights
	int num_samples = 16;

	int vpWidth = 600;
	int vpHeight = 400;

	vp.set_hres(vpWidth);
	vp.set_vres(vpHeight);
	vp.set_samples(num_samples);

	imageWidth = vpWidth;
	imageHeight = vpHeight;
	imageBuffer = new RGBColor[imageWidth * imageHeight];

	tracer_ptr = new RayCast(this);

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);

	float a = 0.75;
	background_color = RGBColor(0.0, 0.3 * a, 0.25 * a);  // torquise

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(7.5, 4, 10);
	pinhole_ptr->set_lookat(-1, 3.7, 0);
	pinhole_ptr->set_view_distance(340);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	Directional* light_ptr1 = new Directional;	// for Figure 15.8(a)
	light_ptr1->set_direction(15, 15, 2.5);
	light_ptr1->scale_radiance(2.0);
	//add_light(light_ptr1);

	PointLight* light_ptr2 = new PointLight;	// for Figure 15.8(b)
	light_ptr2->set_location(15, 15, 2.5);
	light_ptr2->scale_radiance(2.0);
	add_light(light_ptr2);

	
	Phong* phong_ptr1 = new Phong;
	phong_ptr1->set_ka(0.25);
	phong_ptr1->set_kd(0.75);
	phong_ptr1->set_cd(0.75, 0.75, 0);  	// dark yellow
	phong_ptr1->set_ks(0.25);
	phong_ptr1->set_exp(50);

	Phong* phong_ptr2 = new Phong;
	phong_ptr2->set_ka(0.45);
	phong_ptr2->set_kd(0.75);
	phong_ptr2->set_cd(0.75, 0.25, 0);   	// orange
	phong_ptr2->set_ks(0.25);
	phong_ptr2->set_exp(500);
	
	/*
	Matte* phong_ptr1 = new Matte;
	phong_ptr1->set_ka(0.25);
	phong_ptr1->set_kd(0.75);
	phong_ptr1->set_cd(0.75, 0.75, 0);  	// dark yellow

	Matte* phong_ptr2 = new Matte;
	phong_ptr2->set_ka(0.45);
	phong_ptr2->set_kd(0.75);
	phong_ptr2->set_cd(0.75, 0.25, 0);   	// orange
	*/

	
	Matte* matte_ptr5 = new Matte;
	matte_ptr5->set_ka(0.20);
	matte_ptr5->set_kd(0.97);
	matte_ptr5->set_cd(white);


	// spheres

	Sphere* sphere_ptr1 = new Sphere(Point3D(3.85, 2.3, -2.55), 2.3);
	sphere_ptr1->set_material(phong_ptr1);
	add_object(sphere_ptr1);

	Sphere* sphere_ptr2 = new Sphere(Point3D(-0.7, 1, 4.2), 2);
	sphere_ptr2->set_material(phong_ptr2);
	add_object(sphere_ptr2);

	// ground plane

	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr5);
	add_object(plane_ptr);


	// test Matte material and lights

	//int num_samples = 16;
	//int vpWidth = 400;
	//int vpHeight = 400;
	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_pixel_size(0.5);
	//vp.set_samples(num_samples);

	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//tracer_ptr = new RayCast(this);

	//Ambient* ambient_ptr = new Ambient;
	//ambient_ptr->scale_radiance(1.0);
	//set_ambient_light(ambient_ptr);

	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(0, 0, 500);
	//pinhole_ptr->set_lookat(-5, 0, 0);
	//pinhole_ptr->set_view_distance(850.0);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);

	//PointLight* light_ptr2 = new PointLight;
	//light_ptr2->set_location(100, 50, 150);
	//light_ptr2->scale_radiance(3.0);
	//add_light(light_ptr2);

	///*Directional* light_ptr3 = new Directional();
	//light_ptr3->set_direction(100, 50, 150);
	//light_ptr3->scale_radiance(3.0);
	//add_light(light_ptr3);*/

	//Matte* matte_ptr1 = new Matte();
	//matte_ptr1->set_ka(0.25);
	//matte_ptr1->set_kd(0.65);
	//matte_ptr1->set_cd(1, 1, 0);	  				// yellow	
	//Sphere*	sphere_ptr1 = new Sphere(Point3D(10, -5, 0), 27);
	//sphere_ptr1->set_material(matte_ptr1);
	//add_object(sphere_ptr1);

	//Matte* matte_ptr2 = new Matte();
	//matte_ptr2->set_ka(0.15);
	//matte_ptr2->set_kd(0.85);
	//matte_ptr2->set_cd(0.71, 0.40, 0.16);   		// brown
	//Sphere*	sphere_ptr2 = new Sphere(Point3D(-25, 10, -35), 27);
	//sphere_ptr2->set_material(matte_ptr2);
	//add_object(sphere_ptr2);

	//Matte* matte_ptr3 = new Matte();
	//matte_ptr3->set_ka(0.15);
	//matte_ptr3->set_kd(0.5);
	//matte_ptr3->set_cd(0, 0.4, 0.2);				// dark green
	//Plane* plane_ptr = new Plane(Point3D(0, 0, -50), Normal(0, 0, 1));
	//plane_ptr->set_material(matte_ptr3);
	//add_object(plane_ptr);

}


