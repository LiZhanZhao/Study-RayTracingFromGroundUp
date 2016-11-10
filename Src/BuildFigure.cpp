// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.



// Material
#include "Matte.h"
#include "Phong.h"
#include "Emissive.h"

// Light
#include "Ambient.h"
#include "Directional.h"
#include "PointLight.h"
#include "AmbientOccluder.h"
#include "AreaLight.h"

// Cameras
#include "Pinhole.h"
//#include "ThinLens.h"
//#include "Fisheye.h"
//#include "Spherical.h"
//#include "StereoCamera.h"

// Tracers
//#include "SingleSphere.h"
//#include "MultipleObjects.h"
//#include "RayCast.h"
#include "AreaLighting.h"

// Geometric objects
#include "Plane.h"
#include "Sphere.h"
#include "Rectangle.h"

void World::build(void) {

	int vpWidth = 400;
	int vpHeight = 400;

	int num_samples = 1;   		// for Figure 18.4(a)
	//	int num_samples = 100;   	// for Figure 18.4(b) & (c)

	Sampler* sampler_ptr = new MultiJittered(num_samples);

	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_sampler(sampler_ptr);

	imageWidth = vpWidth;
	imageHeight = vpHeight;
	imageBuffer = new RGBColor[imageWidth * imageHeight];

	background_color = RGBColor(0.5);

	tracer_ptr = new AreaLighting(this);

	Pinhole* camera = new Pinhole;
	camera->set_eye(-20, 10, 20);
	camera->set_lookat(0, 2, 0);
	camera->set_view_distance(1080);
	camera->compute_uvw();
	set_camera(camera);


	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->scale_radiance(40.0);
	emissive_ptr->set_ce(white);


	// define a rectangle for the rectangular light

	float width = 4.0;				// for Figure 18.4(a) & (b)
	float height = 4.0;
	//	float width = 2.0;				// for Figure 18.4(c)
	//	float height = 2.0;
	Point3D center(0.0, 7.0, -7.0);	// center of each area light (rectangular, disk, and spherical)
	Point3D p0(-0.5 * width, center.y - 0.5 * height, center.z);
	Vector3D a(width, 0.0, 0.0);
	Vector3D b(0.0, height, 0.0);
	Normal normal(0, 0, 1);

	Rectangle* rectangle_ptr = new Rectangle(p0, a, b, normal);
	rectangle_ptr->set_material(emissive_ptr);
	rectangle_ptr->set_sampler(sampler_ptr);
	rectangle_ptr->set_shadows(false);
	add_object(rectangle_ptr);


	AreaLight* area_light_ptr = new AreaLight;
	area_light_ptr->set_object(rectangle_ptr);
	area_light_ptr->set_shadows(true);
	add_light(area_light_ptr);


	// Four axis aligned boxes

	float box_width = 1.0; 		// x dimension
	float box_depth = 1.0; 		// z dimension
	float box_height = 4.5; 		// y dimension
	float gap = 3.0;

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0.4, 0.7, 0.4);     // green

	/*Box* box_ptr0 = new Box(Point3D(-1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth),
		Point3D(-1.5 * gap - box_width, box_height, 0.5 * box_depth));
	box_ptr0->set_material(matte_ptr1);
	add_object(box_ptr0);*/

	Sphere* sphere_ptr0 = new Sphere(
		Point3D(-1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth), 2.0f);
	sphere_ptr0->set_material(matte_ptr1);
	add_object(sphere_ptr0);

	/*Box* box_ptr1 = new Box(Point3D(-0.5 * gap - box_width, 0.0, -0.5 * box_depth),
		Point3D(-0.5 * gap, box_height, 0.5 * box_depth));
	box_ptr1->set_material(matte_ptr1);
	add_object(box_ptr1);*/

	Sphere* sphere_ptr1 = new Sphere(
		Point3D(-0.5 * gap - box_width, 0.0, -0.5 * box_depth), 2.0f);
	sphere_ptr1->set_material(matte_ptr1);
	add_object(sphere_ptr1);


	/*Box* box_ptr2 = new Box(Point3D(0.5 * gap, 0.0, -0.5 * box_depth),
		Point3D(0.5 * gap + box_width, box_height, 0.5 * box_depth));
	box_ptr2->set_material(matte_ptr1);
	add_object(box_ptr2);*/

	Sphere* sphere_ptr2 = new Sphere(
		Point3D(0.5 * gap, 0.0, -0.5 * box_depth), 2.0f);
	sphere_ptr2->set_material(matte_ptr1);
	add_object(sphere_ptr2);


	/*Box* box_ptr3 = new Box(Point3D(1.5 * gap + box_width, 0.0, -0.5 * box_depth),
		Point3D(1.5 * gap + 2.0 * box_width, box_height, 0.5 * box_depth));
	box_ptr3->set_material(matte_ptr1);
	add_object(box_ptr3);*/

	Sphere* box_ptr3 = new Sphere(
		Point3D(1.5 * gap + box_width, 0.0, -0.5 * box_depth), 2.0f);
	box_ptr3->set_material(matte_ptr1);
	add_object(box_ptr3);


	// ground plane

	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.1);
	matte_ptr2->set_kd(0.90);
	matte_ptr2->set_cd(white);

	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);


	//int vpWidth = 400;
	//int vpHeight = 400;

	////int num_samples = 1;
	//int num_samples = 64;

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);

	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//tracer_ptr = new RayCast(this);

	//MultiJittered* sampler_ptr = new MultiJittered(num_samples);


	//Ambient* ambient_ptr = new Ambient;
	//ambient_ptr->scale_radiance(1.0);
	////set_ambient_light(ambient_ptr);

	//AmbientOccluder* occluder_ptr = new AmbientOccluder;
	//occluder_ptr->scale_radiance(1.0);
	//occluder_ptr->set_min_amount(0.0);
	//occluder_ptr->set_sampler(sampler_ptr);
	//set_ambient_light(occluder_ptr);


	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(25, 20, 45);
	//pinhole_ptr->set_lookat(0, 1, 0);
	//pinhole_ptr->set_view_distance(5000);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);

	//// sphere

	//Matte* matte_ptr1 = new Matte;
	//matte_ptr1->set_ka(0.75);
	//matte_ptr1->set_kd(0);
	//matte_ptr1->set_cd(1, 1, 0);   // yellow

	//Sphere* sphere_ptr = new Sphere(Point3D(0, 1, 0), 1);
	//sphere_ptr->set_material(matte_ptr1);
	//add_object(sphere_ptr);

	//// ground plane

	//Matte* matte_ptr2 = new Matte;
	//matte_ptr2->set_ka(0.75);
	//matte_ptr2->set_kd(0);
	//matte_ptr2->set_cd(white);

	//Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	//plane_ptr->set_material(matte_ptr2);
	//add_object(plane_ptr);






	//int num_samples = 1;
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
	//pinhole_ptr->set_lookat(-15, -10, 0);
	//pinhole_ptr->set_view_distance(850.0);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);
	//
	///*
	//PointLight* light_ptr2 = new PointLight;
	//light_ptr2->set_location(100, 50, 150);
	//light_ptr2->scale_radiance(3.0);
	//light_ptr2->set_shadows(true);
	//add_light(light_ptr2);
	//*/

	//
	//Directional* light_ptr1 = new Directional;
	//light_ptr1->set_direction(100, 50, 150);
	//light_ptr1->scale_radiance(3.0);
	//light_ptr1->set_shadows(true);
	//add_light(light_ptr1);
	//
	////Matte* matte_ptr1 = new Matte;
	////matte_ptr1->set_ka(0.25);
	////matte_ptr1->set_kd(0.65);
	////matte_ptr1->set_cd(1, 1, 0);	  				// yellow	

	//Phong* phong_ptr1 = new Phong();
	//phong_ptr1->set_ka(0.25);
	//phong_ptr1->set_kd(0.65);
	//phong_ptr1->set_cd(1, 1, 0);	
	//phong_ptr1->set_ks(0.25);
	//phong_ptr1->set_exp(50);

	//Sphere*	sphere_ptr1 = new Sphere(Point3D(10, -5, 0), 27);
	//sphere_ptr1->set_material(phong_ptr1);
	//add_object(sphere_ptr1);

	////Matte* matte_ptr2 = new Matte;
	////matte_ptr2->set_ka(0.15);
	////matte_ptr2->set_kd(0.85);
	////matte_ptr2->set_cd(0.71, 0.40, 0.16);   		// brown

	//Phong* phong_ptr2 = new Phong();
	//phong_ptr2->set_ka(0.15);
	//phong_ptr2->set_kd(0.85);
	//phong_ptr2->set_cd(0.71, 0.40, 0.16);
	//phong_ptr2->set_ks(0.25);
	//phong_ptr2->set_exp(50);
	////phong_ptr2->set_shadows(false);

	//Sphere*	sphere_ptr2 = new Sphere(Point3D(-25, 10, -35), 27);
	//sphere_ptr2->set_material(phong_ptr2);
	//add_object(sphere_ptr2);

	//Matte* matte_ptr3 = new Matte;
	//matte_ptr3->set_ka(0.15);
	//matte_ptr3->set_kd(0.5);
	//matte_ptr3->set_cd(0, 0.4, 0.2);				// dark green
	//matte_ptr3->set_shadows(false);

	//Plane* plane_ptr = new Plane(Point3D(0, 0, -50), Normal(0, 0, 1));
	//plane_ptr->set_material(matte_ptr3);
	//add_object(plane_ptr);

	////plane_ptr->set_shadows(false);
}


