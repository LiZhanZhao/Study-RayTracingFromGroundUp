// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.



// Material
#include "Matte.h"
#include "Phong.h"
#include "Emissive.h"
#include "Reflective.h"
#include "GlossyReflector.h"
#include "Transparent.h"
#include "Dielectric.h"

// Light
#include "Ambient.h"
#include "Directional.h"
#include "PointLight.h"
#include "AmbientOccluder.h"
#include "AreaLight.h"
#include "EnvironmentLight.h"

// Cameras
#include "Pinhole.h"
//#include "ThinLens.h"
#include "Fisheye.h"
//#include "Spherical.h"
//#include "StereoCamera.h"

// Tracers
//#include "SingleSphere.h"
//#include "MultipleObjects.h"
//#include "RayCast.h"
#include "AreaLighting.h"
#include "Whitted.h"
#include "PathTrace.h"
#include "GlobalTrace.h"


// Geometric objects
#include "Plane.h"
#include "Sphere.h"
#include "Rectangle.h"
#include "Instance.h"
#include "Grid.h"
#include "Box.h"

void World::build(void) {
	int vpWidth = 600;
	int vpHeight = 400;
	int num_samples = 9;
	imageWidth = vpWidth;
	imageHeight = vpHeight;
	imageBuffer = new RGBColor[imageWidth * imageHeight];

	vp.set_hres(vpWidth);
	vp.set_vres(vpHeight);
	vp.set_samples(num_samples);
	//vp.set_max_depth(15);
	vp.set_max_depth(11);

	tracer_ptr = new Whitted(this);

	background_color = RGBColor(0.75);

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);


	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(10, 12, 20);
	pinhole_ptr->set_lookat(-3.75, 3, 0);
	pinhole_ptr->set_view_distance(1500.0);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(20, 25, -20);
	light_ptr1->scale_radiance(3.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);


	float c = 1.75;  // this allows us to adjust the filter color without changing the hue
	RGBColor glass_color(0.27*c, 0.49*c, 0.42*c);


	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->set_eta_in(1.50);		// glass
	glass_ptr->set_eta_out(1.0);		// air
	glass_ptr->set_cf_in(glass_color);
	glass_ptr->set_cf_out(white);

	double 	thickness = 0.25;
	double 	height = 4.0;
	double 	delta = 1.0;			// length change of each box

	int 	num_boxes = 10;
	double 	x_min = -10.0;		// where the boxes start in the x direction
	double 	gap = 0.5;   		// gap between the boxes

	for (int j = 0; j < num_boxes; j++) {
		double length = thickness + j * delta;
		Point3D p0(x_min + j * (thickness + gap), 0.0, -length);
		Point3D p1(x_min + j * (thickness + gap) + thickness, height, 0.0);

		Box* box_ptr = new Box(p0, p1);
		box_ptr->set_material(glass_ptr);
		add_object(box_ptr);
	}


	// plane

	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(0.5);
	matte_ptr->set_kd(0.65);
	matte_ptr->set_cd(0.75);

	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr);
	add_object(plane_ptr);






	//int vpWidth = 600;
	//int vpHeight = 600;

	////int num_samples = 25;
	//int num_samples = 1;
	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];


	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);
	//vp.set_max_depth(5);

	//background_color = RGBColor(0.9, 0.9, 1);  // pale blue

	//tracer_ptr = new Whitted(this);

	//Ambient* ambient_ptr = new Ambient;
	//ambient_ptr->scale_radiance(0.5);
	//set_ambient_light(ambient_ptr);


	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(0, 1.5, 4);
	//pinhole_ptr->set_lookat(0.0);
	//pinhole_ptr->set_view_distance(675.0);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);


	//PointLight* light_ptr = new PointLight;
	//light_ptr->set_location(10, 20, 20);
	//light_ptr->scale_radiance(7.5);
	//light_ptr->set_shadows(false);
	//add_light(light_ptr);


	//// matte sphere inside cube

	//Matte* matte_ptr = new Matte;
	//matte_ptr->set_ka(0.5);
	//matte_ptr->set_kd(0.5);
	//matte_ptr->set_cd(0.0, 0.25, 1.0);

	//Sphere*	sphere_ptr = new Sphere(Point3D(0.0, -0.25, -1.0), 0.5);
	//sphere_ptr->set_material(matte_ptr);
	//add_object(sphere_ptr);


	//// transparent cube

	//RGBColor glass_color(0.64, 0.98, 0.88);	// light cyan

	//Dielectric* glass_ptr = new Dielectric;
	//glass_ptr->set_exp(2000.0);
	//glass_ptr->set_eta_in(1.5);					// glass
	//glass_ptr->set_eta_out(1.33);				// water
	//glass_ptr->set_cf_in(glass_color);
	//glass_ptr->set_cf_out(white);
	//glass_ptr->set_shadows(false);

	//Box* box_ptr = new Box(Point3D(-1.0), Point3D(1.0));
	//box_ptr->set_material(glass_ptr);
	//add_object(box_ptr);


	//// plane

	////Checker3D* checker_ptr = new Checker3D;
	////checker_ptr->set_size(4.0);
	////checker_ptr->set_color1(1, 1, 0.4);    		// yellow
	////checker_ptr->set_color2(1, 0.5, 0);   		// orange

	//Matte* sv_matte_ptr = new Matte;
	//sv_matte_ptr->set_ka(0.5);
	//sv_matte_ptr->set_kd(0.2);
	//sv_matte_ptr->set_cd(0.37, 0.59, 0.2);
	////sv_matte_ptr->set_cd(checker_ptr);

	//Plane* plane_ptr = new Plane(Point3D(0, -10.1, 0), Normal(0, 1, 0));
	//plane_ptr->set_material(sv_matte_ptr);
	//add_object(plane_ptr);







	//int vpWidth = 600;
	//int vpHeight = 600;
	////int num_samples = 25;
	//int num_samples = 1;
	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);
	////vp.set_max_depth(2);				// for Figure 28.20(a)
	////vp.set_max_depth(3);				// for Figure 28.20(b)
	//vp.set_max_depth(4);				// for Figure 28.20(c)

	//background_color = RGBColor(0.9, 0.9, 1);  // pale blue

	//tracer_ptr = new Whitted(this);

	//Ambient* ambient_ptr = new Ambient;
	//ambient_ptr->scale_radiance(0.5);
	//set_ambient_light(ambient_ptr);


	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(0, 0, 3);
	//pinhole_ptr->set_lookat(0.0);
	//pinhole_ptr->set_view_distance(450);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);


	//PointLight* light_ptr = new PointLight;
	//light_ptr->set_location(10, 20, 20);
	//light_ptr->scale_radiance(15.0);
	//add_light(light_ptr);


	//// transparent cube

	//RGBColor glass_color(0.64, 0.98, 0.88);	// light cyan

	//Dielectric* glass_ptr = new Dielectric;
	//glass_ptr->set_exp(2000.0);
	//glass_ptr->set_eta_in(1.5);					// glass
	//glass_ptr->set_eta_out(1.0);				// air
	//glass_ptr->set_cf_in(glass_color);
	//glass_ptr->set_cf_out(white);
	//glass_ptr->set_shadows(false);

	//Box* box_ptr = new Box(Point3D(-1.0), Point3D(1.0));
	//box_ptr->set_material(glass_ptr);
	//add_object(box_ptr);


	//// plane

	////Checker3D* checker_ptr = new Checker3D;
	////checker_ptr->set_size(4.0);
	////checker_ptr->set_color1(1, 1, 0.4);    		// yellow
	////checker_ptr->set_color2(1, 0.5, 0);   		// orange

	////SV_Matte* sv_matte_ptr = new SV_Matte;
	//Matte* sv_matte_ptr = new Matte;
	//sv_matte_ptr->set_ka(0.5);
	//sv_matte_ptr->set_kd(0.1);
	////sv_matte_ptr->set_cd(checker_ptr);
	//sv_matte_ptr->set_cd(0.37, 0.59, 0.2);

	//Plane* plane_ptr = new Plane(Point3D(0, -10.1, 0), Normal(0, 1, 0));
	//plane_ptr->set_material(sv_matte_ptr);
	//add_object(plane_ptr);












	//int vpWidth = 600;
	//int vpHeight = 400;
	//int num_samples = 16;
	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];


	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);
	//vp.set_max_depth(6);

	//background_color = white;

	//tracer_ptr = new Whitted(this);

	//Ambient* ambient_ptr = new Ambient;
	//ambient_ptr->scale_radiance(0.25);
	//set_ambient_light(ambient_ptr);


	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(2.8125, 0, 1000);
	//pinhole_ptr->set_lookat(2.8125, 0, 0);
	//pinhole_ptr->set_view_distance(50000.0);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);


	//Dielectric* dielectric_ptr = new Dielectric;
	//dielectric_ptr->set_ka(0.0);
	//dielectric_ptr->set_kd(0.0);
	//dielectric_ptr->set_ks(0.0);
	//dielectric_ptr->set_exp(2000);
	//dielectric_ptr->set_eta_in(1.5);
	//dielectric_ptr->set_eta_out(1.0);
	//dielectric_ptr->set_cf_in(0.65, 0.45, 0);   // orange
	//dielectric_ptr->set_cf_out(1.0);


	//// a row of spheres

	//Sphere* sphere_ptr1 = new Sphere(Point3D(0), 3.0);
	//sphere_ptr1->set_material(dielectric_ptr);
	//add_object(sphere_ptr1);


	//Sphere* sphere_ptr2 = new Sphere(Point3D(4.5, 0, 0), 1.5);
	//sphere_ptr2->set_material(dielectric_ptr);
	//add_object(sphere_ptr2);


	//Sphere* sphere_ptr3 = new Sphere(Point3D(6.75, 0, 0), 0.75);
	//sphere_ptr3->set_material(dielectric_ptr);
	//add_object(sphere_ptr3);

	//Sphere* sphere_ptr4 = new Sphere(Point3D(7.875, 0, 0), 0.375);
	//sphere_ptr4->set_material(dielectric_ptr);
	//add_object(sphere_ptr4);

	//Sphere* sphere_ptr5 = new Sphere(Point3D(8.4375, 0, 0), 0.1875);
	//sphere_ptr5->set_material(dielectric_ptr);
	//add_object(sphere_ptr5);









	/*int vpWidth = 600;
	int vpHeight = 600;
	int num_samples = 16;

	imageWidth = vpWidth;
	imageHeight = vpHeight;
	imageBuffer = new RGBColor[imageWidth * imageHeight];

	vp.set_hres(vpWidth);
	vp.set_vres(vpHeight);
	vp.set_samples(num_samples);
	vp.set_max_depth(3);

	background_color = white;

	tracer_ptr = new Whitted(this);

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 50);
	pinhole_ptr->set_lookat(0);
	pinhole_ptr->set_view_distance(4200.0);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);


	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_ka(0.0);
	dielectric_ptr->set_kd(0.0);
	dielectric_ptr->set_ks(0.2);
	dielectric_ptr->set_exp(2000.0);
	dielectric_ptr->set_eta_in(1.5);
	dielectric_ptr->set_eta_out(1.0);
	dielectric_ptr->set_cf_in(white);
	dielectric_ptr->set_cf_out(white);

	Sphere* sphere_ptr1 = new Sphere(Point3D(0), 3);
	sphere_ptr1->set_material(dielectric_ptr);
	add_object(sphere_ptr1);*/







	//
	//int vpWidth = 600;
	//int vpHeight = 600;
	//int num_samples = 1;

	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(imageWidth);
	//vp.set_vres(imageHeight);
	//vp.set_samples(num_samples);
	//vp.set_max_depth(5);

	//background_color = RGBColor(0.0, 0.3, 0.25);

	//tracer_ptr = new Whitted(this);

	//Ambient* ambient_ptr = new Ambient;
	//ambient_ptr->scale_radiance(0.25);
	//set_ambient_light(ambient_ptr);

	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(-8, 5.5, 40);
	//pinhole_ptr->set_lookat(1, 4, 0);
	//pinhole_ptr->set_view_distance(2400.0);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);


	//// point light 

	//PointLight* light_ptr1 = new PointLight;
	//light_ptr1->set_location(40, 50, 0);
	//light_ptr1->scale_radiance(4.5);
	//light_ptr1->set_shadows(true);
	//add_light(light_ptr1);


	//// point light 

	//PointLight* light_ptr2 = new PointLight;
	//light_ptr2->set_location(-10, 20, 10);
	//light_ptr2->scale_radiance(4.5);
	//light_ptr2->set_shadows(true);
	//add_light(light_ptr2);


	//// directional light 

	//Directional* light_ptr3 = new Directional;
	//light_ptr3->set_direction(-1, 0, 0);
	//light_ptr3->scale_radiance(4.5);
	//light_ptr3->set_shadows(true);
	//add_light(light_ptr3);


	//// transparent sphere

	//Dielectric* dielectic_ptr = new Dielectric;
	//dielectic_ptr->set_ks(0.2);
	//dielectic_ptr->set_exp(2000.0);
	////dielectic_ptr->set_eta_in(1.5);		// for Figure 28.5(a)
	//dielectic_ptr->set_eta_in(0.75);	// for Figure 28.5(b)
	//dielectic_ptr->set_eta_out(1.0);
	//dielectic_ptr->set_cf_in(white);
	//dielectic_ptr->set_cf_out(white);

	//Sphere* sphere_ptr1 = new Sphere(Point3D(0.0, 4.5, 0.0), 3.0);
	//sphere_ptr1->set_material(dielectic_ptr);
	//add_object(sphere_ptr1);


	//// red sphere

	//Reflective*	reflective_ptr = new Reflective;
	//reflective_ptr->set_ka(0.3);
	//reflective_ptr->set_kd(0.3);
	//reflective_ptr->set_cd(red);
	//reflective_ptr->set_ks(0.2);
	//reflective_ptr->set_exp(2000.0);
	//reflective_ptr->set_kr(0.25);

	//Sphere* sphere_ptr2 = new Sphere(Point3D(4, 4, -6), 3);
	//sphere_ptr2->set_material(reflective_ptr);
	//add_object(sphere_ptr2);


	///*Checker3D* checker_ptr = new Checker3D;
	//checker_ptr->set_size(4);
	//checker_ptr->set_color1(0.75);
	//checker_ptr->set_color2(white);*/

	///*SV_Matte* sv_matte_ptr = new SV_Matte;
	//sv_matte_ptr->set_ka(0.5);
	//sv_matte_ptr->set_kd(0.35);
	//sv_matte_ptr->set_cd(checker_ptr);*/

	//Matte* sv_matte_ptr = new Matte;
	//sv_matte_ptr->set_ka(0.5);
	//sv_matte_ptr->set_kd(0.35);
	//sv_matte_ptr->set_cd(0.37, 0.59, 0.2);

	//// rectangle

	//Point3D p0(-20, 0, -100);
	//Vector3D a(0, 0, 120);
	//Vector3D b(40, 0, 0);

	//Rectangle* rectangle_ptr = new Rectangle(p0, a, b);
	//rectangle_ptr->set_material(sv_matte_ptr);
	//add_object(rectangle_ptr);







	//int vpWidth = 600;
	//int vpHeight = 600;
	//int num_samples = 16;
	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);
	//vp.set_max_depth(2);			// for Figure 27.13(a)
	////	vp.set_max_depth(4);			// for Figure 27.13(b)
	////	vp.set_max_depth(5);			// for Figure 27.13(c)	

	//background_color = RGBColor(0.0, 0.3, 0.25);

	//tracer_ptr = new Whitted(this);

	//Ambient* ambient_ptr = new Ambient;
	//ambient_ptr->scale_radiance(0.25);
	//set_ambient_light(ambient_ptr);

	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(-8, 5.5, 40);
	//pinhole_ptr->set_lookat(1, 4, 0);
	//pinhole_ptr->set_view_distance(2400.0);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);


	//// point light 

	//PointLight* light_ptr1 = new PointLight;
	//light_ptr1->set_location(40, 50, 0);
	//light_ptr1->scale_radiance(4.5);
	//light_ptr1->set_shadows(true);
	////light_ptr1->set_shadows(false);
	//add_light(light_ptr1);


	//// point light 

	//PointLight* light_ptr2 = new PointLight;
	//light_ptr2->set_location(-10, 20, 10);
	//light_ptr2->scale_radiance(4.5);
	//light_ptr2->set_shadows(true);
	////light_ptr2->set_shadows(false);
	//add_light(light_ptr2);


	//// directional light 

	//Directional* light_ptr3 = new Directional;
	//light_ptr3->set_direction(-1, 0, 0);
	//light_ptr3->scale_radiance(4.5);
	//light_ptr3->set_shadows(true);
	////light_ptr3->set_shadows(false);
	//add_light(light_ptr3);


	//// transparent sphere

	//Transparent* glass_ptr = new Transparent;
	//glass_ptr->set_ks(0.2);
	//glass_ptr->set_exp(2000.0);
	////glass_ptr->set_ior(1.0);
	////glass_ptr->set_ior(1.5);
	//glass_ptr->set_ior(0.75);
	//glass_ptr->set_kr(0.1);
	////glass_ptr->set_kr(1);
	//glass_ptr->set_kt(0.9);

	//Sphere* sphere_ptr1 = new Sphere(Point3D(0.0, 4.5, 0.0), 3.0);
	//sphere_ptr1->set_material(glass_ptr);
	//add_object(sphere_ptr1);


	//// red sphere

	//Reflective*	reflective_ptr = new Reflective;
	//reflective_ptr->set_ka(0.3);
	//reflective_ptr->set_kd(0.3);
	//reflective_ptr->set_cd(red);
	//reflective_ptr->set_ks(0.2);
	//reflective_ptr->set_exp(2000.0);
	//reflective_ptr->set_kr(0.25);

	//Sphere* sphere_ptr2 = new Sphere(Point3D(4, 4, -6), 3);
	//sphere_ptr2->set_material(reflective_ptr);
	//add_object(sphere_ptr2);


	////Checker3D* checker_ptr = new Checker3D;
	////checker_ptr->set_size(4);
	////checker_ptr->set_color1(0.75);
	////checker_ptr->set_color2(white);

	////SV_Matte* sv_matte_ptr = new SV_Matte;
	//Matte* sv_matte_ptr = new Matte;
	//sv_matte_ptr->set_ka(0.5);
	//sv_matte_ptr->set_kd(0.35);
	//sv_matte_ptr->set_cd(0.37, 0.59, 0.2);
	////sv_matte_ptr->set_cd(checker_ptr);

	//// rectangle

	//Point3D p0(-20, 0, -100);
	//Vector3D a(0, 0, 120);
	//Vector3D b(40, 0, 0);

	//Rectangle* rectangle_ptr = new Rectangle(p0, a, b);
	//rectangle_ptr->set_material(sv_matte_ptr);
	//add_object(rectangle_ptr);
}


