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
#include "EnvironmentLight.h"

// Cameras
#include "Pinhole.h"
//#include "ThinLens.h"
//#include "Fisheye.h"
//#include "Spherical.h"
//#include "StereoCamera.h"

// Tracers
//#include "SingleSphere.h"
//#include "MultipleObjects.h"
#include "RayCast.h"
//#include "AreaLighting.h"


// Geometric objects
#include "Plane.h"
#include "Sphere.h"
#include "Rectangle.h"
#include "Instance.h"

void World::build(void) {
	int vpWidth = 400;
	int vpHeight = 400;
	int num_samples = 16;

	imageWidth = vpWidth;
	imageHeight = vpHeight; 
	imageBuffer = new RGBColor[imageWidth * imageHeight];

	vp.set_hres(imageWidth);
	vp.set_vres(imageHeight);
	vp.set_samples(num_samples);

	tracer_ptr = new RayCast(this);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(100, 0, 100);
	pinhole_ptr->set_lookat(0, 1, 0);
	pinhole_ptr->set_view_distance(8000);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(50, 50, 1);
	light_ptr->scale_radiance(3.0);
	add_light(light_ptr);

	Phong* phong_ptr = new Phong;
	phong_ptr->set_cd(0.75);
	phong_ptr->set_ka(0.25);
	phong_ptr->set_kd(0.8);
	phong_ptr->set_ks(0.15);
	phong_ptr->set_exp(50.0);

	// node: this is have a sphere
	Instance* ellipsoid_ptr = new Instance(new Sphere);
	ellipsoid_ptr->set_material(phong_ptr);
	ellipsoid_ptr->scale(2, 3, 1);
	ellipsoid_ptr->rotate_x(-45);
	ellipsoid_ptr->translate(0, 1, 0);
	add_object(ellipsoid_ptr);

	//int vpWidth = 600;
	//int vpHeight = 400;

	//int num_samples = 100;

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);

	//imageWidth = vpWidth;
	//imageHeight = vpHeight; 
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//tracer_ptr = new AreaLighting(this);

	///*AmbientOccluder* ambient_occluder_ptr = new AmbientOccluder;
	//ambient_occluder_ptr->set_sampler(new MultiJittered(num_samples));
	//ambient_occluder_ptr->set_min_amount(0.5);
	//set_ambient_light(ambient_occluder_ptr);*/


	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(100, 45, 100);
	//pinhole_ptr->set_lookat(-10, 40, 0);
	//pinhole_ptr->set_view_distance(400);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);


	//Emissive* emissive_ptr = new Emissive;
	//emissive_ptr->scale_radiance(0.90);
	////emissive_ptr->set_ce(1.0, 1.0, 0.5); 	// yellow 	for Figure 18.8(a)
	//emissive_ptr->set_ce(0.5, 0.65, 0.75);  // blue		for Figure 18.8(b)


	///*ConcaveSphere* sphere_ptr = new ConcaveSphere;
	//sphere_ptr->set_radius(1000000.0);
	//sphere_ptr->set_material(emissive_ptr);
	//sphere_ptr->set_shadows(false);
	//add_object(sphere_ptr);*/

	//EnvironmentLight* environment_light_ptr = new EnvironmentLight;
	//environment_light_ptr->set_material(emissive_ptr);
	//environment_light_ptr->set_sampler(new MultiJittered(num_samples));
	//environment_light_ptr->set_shadows(true);
	//add_light(environment_light_ptr);


	//float ka = 0.2;  // commom ambient reflection coefficient

	//// large sphere

	//Matte* matte_ptr1 = new Matte;
	//matte_ptr1->set_ka(ka);
	//matte_ptr1->set_kd(0.60);
	//matte_ptr1->set_cd(0.75);

	//Sphere* sphere_ptr1 = new Sphere(Point3D(38, 20, -24), 20);
	//sphere_ptr1->set_material(matte_ptr1);
	//add_object(sphere_ptr1);


	//// small sphere

	//Matte* matte_ptr2 = new Matte;
	//matte_ptr2->set_ka(ka);
	//matte_ptr2->set_kd(0.5);
	//matte_ptr2->set_cd(0.85);

	//Sphere* sphere_ptr2 = new Sphere(Point3D(34, 12, 13), 12);
	//sphere_ptr2->set_material(matte_ptr2);
	//add_object(sphere_ptr2);


	//// medium sphere

	//Matte* matte_ptr3 = new Matte;
	//matte_ptr3->set_ka(ka);
	//matte_ptr3->set_kd(0.5);
	//matte_ptr3->set_cd(0.75);

	//Sphere* sphere_ptr3 = new Sphere(Point3D(-7, 15, 42), 16);
	//sphere_ptr3->set_material(matte_ptr3);
	//add_object(sphere_ptr3);


	//// cylinder

	//Matte* matte_ptr4 = new Matte;
	//matte_ptr4->set_ka(ka);
	//matte_ptr4->set_kd(0.5);
	//matte_ptr4->set_cd(0.60);

	///*float bottom = 0.0;
	//float top = 85;
	//float radius = 22;
	//SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	//cylinder_ptr->set_material(matte_ptr4);
	//add_object(cylinder_ptr);*/


	//// box

	//Matte* matte_ptr5 = new Matte;
	//matte_ptr5->set_ka(ka);
	//matte_ptr5->set_kd(0.5);
	//matte_ptr5->set_cd(0.95);

	///*Box* box_ptr = new Box(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	//box_ptr->set_material(matte_ptr5);
	//add_object(box_ptr);*/


	//// ground plane

	//Matte* matte_ptr6 = new Matte;
	//matte_ptr6->set_ka(0.15);
	//matte_ptr6->set_kd(0.5);
	//matte_ptr6->set_cd(0.7);

	//Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	//plane_ptr->set_material(matte_ptr6);
	//add_object(plane_ptr);
}


