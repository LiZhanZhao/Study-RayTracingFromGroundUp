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
	vp.set_max_depth(2);			// for Figure 27.13(a)
	//	vp.set_max_depth(4);			// for Figure 27.13(b)
	//	vp.set_max_depth(5);			// for Figure 27.13(c)	

	background_color = RGBColor(0.0, 0.3, 0.25);

	tracer_ptr = new Whitted(this);

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(-8, 5.5, 40);
	pinhole_ptr->set_lookat(1, 4, 0);
	pinhole_ptr->set_view_distance(2400.0);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);


	// point light 

	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(40, 50, 0);
	light_ptr1->scale_radiance(4.5);
	light_ptr1->set_shadows(true);
	//light_ptr1->set_shadows(false);
	add_light(light_ptr1);


	// point light 

	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(-10, 20, 10);
	light_ptr2->scale_radiance(4.5);
	light_ptr2->set_shadows(true);
	//light_ptr2->set_shadows(false);
	add_light(light_ptr2);


	// directional light 

	Directional* light_ptr3 = new Directional;
	light_ptr3->set_direction(-1, 0, 0);
	light_ptr3->scale_radiance(4.5);
	light_ptr3->set_shadows(true);
	//light_ptr3->set_shadows(false);
	add_light(light_ptr3);


	// transparent sphere

	Transparent* glass_ptr = new Transparent;
	glass_ptr->set_ks(0.2);
	glass_ptr->set_exp(2000.0);
	//glass_ptr->set_ior(1.0);
	glass_ptr->set_ior(1.5);
	//glass_ptr->set_ior(0.75);
	glass_ptr->set_kr(0.1);
	//glass_ptr->set_kr(1);
	glass_ptr->set_kt(0.9);

	Sphere* sphere_ptr1 = new Sphere(Point3D(0.0, 4.5, 0.0), 3.0);
	sphere_ptr1->set_material(glass_ptr);
	add_object(sphere_ptr1);


	// red sphere

	Reflective*	reflective_ptr = new Reflective;
	reflective_ptr->set_ka(0.3);
	reflective_ptr->set_kd(0.3);
	reflective_ptr->set_cd(red);
	reflective_ptr->set_ks(0.2);
	reflective_ptr->set_exp(2000.0);
	reflective_ptr->set_kr(0.25);

	Sphere* sphere_ptr2 = new Sphere(Point3D(4, 4, -6), 3);
	sphere_ptr2->set_material(reflective_ptr);
	add_object(sphere_ptr2);


	//Checker3D* checker_ptr = new Checker3D;
	//checker_ptr->set_size(4);
	//checker_ptr->set_color1(0.75);
	//checker_ptr->set_color2(white);

	//SV_Matte* sv_matte_ptr = new SV_Matte;
	Matte* sv_matte_ptr = new Matte;
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.35);
	sv_matte_ptr->set_cd(0.37, 0.59, 0.2);
	//sv_matte_ptr->set_cd(checker_ptr);

	// rectangle

	Point3D p0(-20, 0, -100);
	Vector3D a(0, 0, 120);
	Vector3D b(40, 0, 0);

	Rectangle* rectangle_ptr = new Rectangle(p0, a, b);
	rectangle_ptr->set_material(sv_matte_ptr);
	add_object(rectangle_ptr);










	//int vpWidth = 300;
	//int vpHeight = 300;
	//int num_samples = 1;
	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);
	//vp.set_max_depth(0);

	//background_color = black;

	//tracer_ptr = new GlobalTrace(this);

	//Ambient* ambient_ptr = new Ambient;
	//ambient_ptr->scale_radiance(0.0);
	//set_ambient_light(ambient_ptr);


	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(27.6, 27.4, -80.0);
	//pinhole_ptr->set_lookat(27.6, 27.4, 0.0);
	//pinhole_ptr->set_view_distance(400);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);


	//Point3D p0;
	//Vector3D a, b;
	//Normal normal;

	//// box dimensions

	//double width = 55.28;   	// x direction
	//double height = 54.88;  	// y direction
	//double depth = 55.92;	// z direction


	//Emissive* emissive_ptr = new Emissive;
	//emissive_ptr->set_ce(1.0, 0.73, 0.4);
	//emissive_ptr->scale_radiance(100.0);

	//p0 = Point3D(21.3, height - 0.001, 22.7);
	//a = Vector3D(0.0, 0.0, 10.5);
	//b = Vector3D(13.0, 0.0, 0.0);
	//normal = Normal(0.0, -1.0, 0.0);

	//Rectangle* light_ptr = new Rectangle(p0, a, b, normal);
	//light_ptr->set_material(emissive_ptr);
	//light_ptr->set_sampler(new MultiJittered(num_samples));
	//light_ptr->set_shadows(false);
	//add_object(light_ptr);

	//AreaLight* ceiling_light_ptr = new AreaLight;
	//ceiling_light_ptr->set_object(light_ptr);
	//ceiling_light_ptr->set_shadows(true);
	//add_light(ceiling_light_ptr);


	//// left wall

	//Matte* matte_ptr1 = new Matte;
	//matte_ptr1->set_ka(0.0);
	//matte_ptr1->set_kd(0.6);
	//matte_ptr1->set_cd(0.57, 0.025, 0.025);	 // red
	//matte_ptr1->set_sampler(new MultiJittered(num_samples));

	//p0 = Point3D(width, 0.0, 0.0);
	//a = Vector3D(0.0, 0.0, depth);
	//b = Vector3D(0.0, height, 0.0);
	//normal = Normal(-1.0, 0.0, 0.0);
	//Rectangle* left_wall_ptr = new Rectangle(p0, a, b, normal);
	//left_wall_ptr->set_material(matte_ptr1);
	//add_object(left_wall_ptr);


	//// right wall

	//Matte* matte_ptr2 = new Matte;
	//matte_ptr2->set_ka(0.0);
	//matte_ptr2->set_kd(0.6);
	//matte_ptr2->set_cd(0.37, 0.59, 0.2);	 // green  
	//matte_ptr2->set_sampler(new MultiJittered(num_samples));

	//p0 = Point3D(0.0, 0.0, 0.0);
	//a = Vector3D(0.0, 0.0, depth);
	//b = Vector3D(0.0, height, 0.0);
	//normal = Normal(1.0, 0.0, 0.0);
	//Rectangle* right_wall_ptr = new Rectangle(p0, a, b, normal);
	//right_wall_ptr->set_material(matte_ptr2);
	//add_object(right_wall_ptr);


	//// back wall

	//Matte* matte_ptr3 = new Matte;
	//matte_ptr3->set_ka(0.0);
	//matte_ptr3->set_kd(0.6);
	//matte_ptr3->set_cd(white);
	//matte_ptr3->set_sampler(new MultiJittered(num_samples));

	//p0 = Point3D(0.0, 0.0, depth);
	//a = Vector3D(width, 0.0, 0.0);
	//b = Vector3D(0.0, height, 0.0);
	//normal = Normal(0.0, 0.0, -1.0);
	//Rectangle* back_wall_ptr = new Rectangle(p0, a, b, normal);
	//back_wall_ptr->set_material(matte_ptr3);
	//add_object(back_wall_ptr);


	//// floor

	//p0 = Point3D(0.0, 0.0, 0.0);
	//a = Vector3D(0.0, 0.0, depth);
	//b = Vector3D(width, 0.0, 0.0);
	//normal = Normal(0.0, 1.0, 0.0);
	//Rectangle* floor_ptr = new Rectangle(p0, a, b, normal);
	//floor_ptr->set_material(matte_ptr3);
	//add_object(floor_ptr);


	//// ceiling

	//p0 = Point3D(0.0, height, 0.0);
	//a = Vector3D(0.0, 0.0, depth);
	//b = Vector3D(width, 0.0, 0.0);
	//normal = Normal(0.0, -1.0, 0.0);
	//Rectangle* ceiling_ptr = new Rectangle(p0, a, b, normal);
	//ceiling_ptr->set_material(matte_ptr3);
	//add_object(ceiling_ptr);


	//// the two boxes defined as 5 rectangles each

	//// short box

	//// top

	//p0 = Point3D(13.0, 16.5, 6.5);
	//a = Vector3D(-4.8, 0.0, 16.0);
	//b = Vector3D(16.0, 0.0, 4.9);
	//normal = Normal(0.0, 1.0, 0.0);
	//Rectangle* short_top_ptr = new Rectangle(p0, a, b, normal);
	//short_top_ptr->set_material(matte_ptr3);
	//add_object(short_top_ptr);


	//// side 1

	//p0 = Point3D(13.0, 0.0, 6.5);
	//a = Vector3D(-4.8, 0.0, 16.0);
	//b = Vector3D(0.0, 16.5, 0.0);
	//Rectangle* short_side_ptr1 = new Rectangle(p0, a, b);
	//short_side_ptr1->set_material(matte_ptr3);
	//add_object(short_side_ptr1);


	//// side 2

	//p0 = Point3D(8.2, 0.0, 22.5);
	//a = Vector3D(15.8, 0.0, 4.7);
	//Rectangle* short_side_ptr2 = new Rectangle(p0, a, b);
	//short_side_ptr2->set_material(matte_ptr3);
	//add_object(short_side_ptr2);


	//// side 3

	//p0 = Point3D(24.2, 0.0, 27.4);
	//a = Vector3D(4.8, 0.0, -16.0);
	//Rectangle* short_side_ptr3 = new Rectangle(p0, a, b);
	//short_side_ptr3->set_material(matte_ptr3);
	//add_object(short_side_ptr3);


	//// side 4

	//p0 = Point3D(29.0, 0.0, 11.4);
	//a = Vector3D(-16.0, 0.0, -4.9);
	//Rectangle* short_side_ptr4 = new Rectangle(p0, a, b);
	//short_side_ptr4->set_material(matte_ptr3);
	//add_object(short_side_ptr4);



	//// tall box

	//// top

	//p0 = Point3D(42.3, 33.0, 24.7);
	//a = Vector3D(-15.8, 0.0, 4.9);
	//b = Vector3D(4.9, 0.0, 15.9);
	//normal = Normal(0.0, 1.0, 0.0);
	//Rectangle* tall_top_ptr = new Rectangle(p0, a, b, normal);
	//tall_top_ptr->set_material(matte_ptr3);
	//add_object(tall_top_ptr);


	//// side 1

	//p0 = Point3D(42.3, 0.0, 24.7);
	//a = Vector3D(-15.8, 0.0, 4.9);
	//b = Vector3D(0.0, 33.0, 0.0);
	//Rectangle* tall_side_ptr1 = new Rectangle(p0, a, b);
	//tall_side_ptr1->set_material(matte_ptr3);
	//add_object(tall_side_ptr1);


	//// side 2

	//p0 = Point3D(26.5, 0.0, 29.6);
	//a = Vector3D(4.9, 0.0, 15.9);
	//Rectangle* tall_side_ptr2 = new Rectangle(p0, a, b);
	//tall_side_ptr2->set_material(matte_ptr3);
	//add_object(tall_side_ptr2);


	//// side 3

	//p0 = Point3D(31.4, 0.0, 45.5);
	//a = Vector3D(15.8, 0.0, -4.9);
	//Rectangle* tall_side_ptr3 = new Rectangle(p0, a, b);
	//tall_side_ptr3->set_material(matte_ptr3);
	//add_object(tall_side_ptr3);


	//// side 4

	//p0 = Point3D(47.2, 0.0, 40.6);
	//a = Vector3D(-4.9, 0.0, -15.9);
	//Rectangle* tall_side_ptr4 = new Rectangle(p0, a, b);
	//tall_side_ptr4->set_material(matte_ptr3);
	//add_object(tall_side_ptr4);


}


