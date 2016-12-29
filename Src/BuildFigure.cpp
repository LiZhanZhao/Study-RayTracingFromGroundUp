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

void World::build(void) {
	int vpWidth = 600;
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
	add_object(sphere_ptr1);







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


