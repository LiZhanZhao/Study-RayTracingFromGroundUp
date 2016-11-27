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
#include "Fisheye.h"
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
#include "Grid.h"

void World::build(void) {
	int vpWidth = 400;
	int vpHeight = 400;
	int num_samples = 16;

	imageWidth = vpWidth;
	imageHeight = vpHeight; 
	imageBuffer = new RGBColor[imageWidth * imageHeight];

	vp.set_hres(vpWidth);
	vp.set_vres(vpHeight);
	vp.set_samples(num_samples);

	background_color = RGBColor(0.9);

	tracer_ptr = new RayCast(this);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(10, 12, 18);
	pinhole_ptr->set_lookat(0);
	pinhole_ptr->set_view_distance(4000);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);


	Directional* light_ptr = new Directional;
	light_ptr->set_direction(20, 25, 5);
	light_ptr->scale_radiance(3.0);
	light_ptr->set_shadows(false);
	add_light(light_ptr);


	Phong* phong_ptr = new Phong;
	phong_ptr->set_ka(0.25);
	phong_ptr->set_kd(0.75);
	phong_ptr->set_cd(0.5);
	phong_ptr->set_cd(0.2, 0.5, 0.4);
	phong_ptr->set_ks(0.2);
	phong_ptr->set_exp(20.0);

	// 360 must be divisible by num_horizontal_steps
	// 180 must be divisible by num_vertical_steps

	//int num_horizontal_steps = 3;    	// for Figure 23.3(a)
	//int num_vertical_steps = 2;

	//	int num_horizontal_steps = 4;		// for Figure 23.3(b)
	//	int num_vertical_steps = 2;

	//	int num_horizontal_steps = 10;		// for Figure 23.3(c)
	//	int num_vertical_steps = 5;

		int num_horizontal_steps = 100;		// for Figure 23.3(d)
		int num_vertical_steps = 50;

	Grid* grid_ptr = new Grid;
	grid_ptr->tessellate_smooth_sphere(num_horizontal_steps, num_vertical_steps);
	grid_ptr->set_material(phong_ptr);
	grid_ptr->setup_cells();
	add_object(grid_ptr);




	//int vpWidth = 400;
	//int vpHeight = 400;
	//int num_samples = 16;

	//imageWidth = vpWidth;
	//imageHeight = vpHeight; 
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);

	//background_color = RGBColor(0.9);

	//tracer_ptr = new RayCast(this);

	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(10, 12, 18);
	//pinhole_ptr->set_lookat(0);
	//pinhole_ptr->set_view_distance(4000);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);


	//Directional* light_ptr = new Directional;
	//light_ptr->set_direction(20, 25, 5);
	//light_ptr->scale_radiance(3.0);
	//light_ptr->set_shadows(false);
	//add_light(light_ptr);


	//Phong* phong_ptr = new Phong;
	//phong_ptr->set_ka(0.25);
	//phong_ptr->set_kd(0.75);
	//phong_ptr->set_cd(0.5);
	//phong_ptr->set_cd(0.2, 0.5, 0.4);
	//phong_ptr->set_ks(0.2);
	//phong_ptr->set_exp(20.0);

	//// 360 must be divisible by num_horizontal_steps
	//// 180 must be divisible by num_vertical_steps

	////int num_horizontal_steps = 3;    	// for Figure 23.1(a)
	////int num_vertical_steps = 2;

	////	int num_horizontal_steps = 4;		// for Figure 23.1(b)
	////	int num_vertical_steps = 2;

	//	//int num_horizontal_steps = 10;		// for Figure 23.1(c)
	//	//int num_vertical_steps = 5;

	//int num_horizontal_steps = 100;		// for Figure 23.1(d)
	//int num_vertical_steps = 50;

	//Grid* grid_ptr = new Grid;
	//grid_ptr->tessellate_flat_sphere(num_horizontal_steps, num_vertical_steps);
	//grid_ptr->set_material(phong_ptr);
	//grid_ptr->setup_cells();
	//add_object(grid_ptr);





	//int vpWidth = 800;
	//int vpHeight = 400;

	//int num_samples = 1;

	//imageWidth = vpWidth;
	//imageHeight = vpHeight; 
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);

	//tracer_ptr = new RayCast(this);

	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(0, 0, 0);
	//pinhole_ptr->set_lookat(0, 0, 100);
	//pinhole_ptr->set_view_distance(1000);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);

	///*FishEye* fisheye_ptr = new FishEye();
	//fisheye_ptr->set_eye(0, 0, 0);
	//fisheye_ptr->set_lookat(0, 0, 100);
	//fisheye_ptr->set_fov(90);
	//fisheye_ptr->compute_uvw();
	//set_camera(fisheye_ptr);*/


	//Directional* light_ptr1 = new Directional;
	//light_ptr1->set_direction(1, 0, 0);    				// from the +ve x direction     
	//light_ptr1->scale_radiance(1);
	//light_ptr1->set_shadows(true);
	//add_light(light_ptr1);

	//Directional* light_ptr2 = new Directional;
	//light_ptr2->set_direction(0, 1, 0);    				// from the +ve y direction     
	//light_ptr2->scale_radiance(2);
	//light_ptr2->set_shadows(true);
	//add_light(light_ptr2);

	//Directional* light_ptr3 = new Directional;
	//light_ptr3->set_direction(0, 0, 1);    				// from the +ve z direction      
	//light_ptr3->scale_radiance(1.5);
	//light_ptr3->set_shadows(true);
	//add_light(light_ptr3);


	//Directional* light_ptr4 = new Directional;
	//light_ptr4->set_direction(-1, 0, 0);    			// from the -ve x direction     
	//light_ptr4->scale_radiance(1);
	//light_ptr4->set_shadows(true);
	//add_light(light_ptr4);

	//Directional* light_ptr5 = new Directional;
	//light_ptr5->set_direction(0, -1, 0);    			// from the -ve y direction     
	//light_ptr5->scale_radiance(2);
	//light_ptr5->set_shadows(true);
	//add_light(light_ptr5);

	//Directional* light_ptr6 = new Directional;
	//light_ptr6->set_direction(0, 0, -1);    			// from the -ve z direction      
	//light_ptr6->scale_radiance(1.5);
	//light_ptr6->set_shadows(true);
	//add_light(light_ptr6);


	//Grid* grid_ptr = new Grid;

	//int num_spheres = 2;
	//float volume = 0.1 / num_spheres;
	//float radius = 2.5 * pow(0.75 * volume / 3.14159, 0.333333);

	//set_rand_seed(15);

	//for (int j = 0; j < num_spheres; j++) {
	//	Phong* phong_ptr = new Phong;
	//	phong_ptr->set_cd(0.75);
	//	phong_ptr->set_ka(0.25);
	//	phong_ptr->set_kd(0.8);
	//	phong_ptr->set_ks(0.15);
	//	phong_ptr->set_exp(50.0);

	//	Sphere* sphere_ptr1 = new Sphere;
	//	sphere_ptr1->set_material(phong_ptr);

	//	Instance* sphere_ptr2 = new Instance(sphere_ptr1);
	//	sphere_ptr2->scale(radius);
	//	sphere_ptr2->translate(1.0 - 2.0 * rand_float(), 1.0 - 2.0 * rand_float(), 10);
	//	
	//	//sphere_ptr2->translate(1.0 - 2.0 * rand_float(), 1.0 - 2.0 * rand_float(), 1.0 - 2.0 * rand_float());
	//	
	//	sphere_ptr2->compute_bounding_box();

	//	grid_ptr->add_object(sphere_ptr2);
	//}

	//grid_ptr->setup_cells();
	//add_object(grid_ptr);



}


