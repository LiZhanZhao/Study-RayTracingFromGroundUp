// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.




#include "Matte.h"

void World::build(void) {
	
	int num_samples = 16;

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(0.5);
	vp.set_samples(num_samples);

	tracer_ptr = new RayCast(this);

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 500);
	pinhole_ptr->set_lookat(-5, 0, 0);
	//pinhole_ptr->set_vpd(850.0);
	pinhole_ptr->set_view_distance(850.0);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	/*PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(100, 50, 150);
	light_ptr2->scale_radiance(3.0);
	add_light(light_ptr2);*/

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.65);
	matte_ptr1->set_cd(1, 1, 0);	  				// yellow	
	Sphere*	sphere_ptr1 = new Sphere(Point3D(10, -5, 0), 27);
	sphere_ptr1->set_material(matte_ptr1);
	add_object(sphere_ptr1);

	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.15);
	matte_ptr2->set_kd(0.85);
	matte_ptr2->set_cd(0.71, 0.40, 0.16);   		// brown
	Sphere*	sphere_ptr2 = new Sphere(Point3D(-25, 10, -35), 27);
	sphere_ptr2->set_material(matte_ptr2);
	add_object(sphere_ptr2);

	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.15);
	matte_ptr3->set_kd(0.5);
	matte_ptr3->set_cd(0, 0.4, 0.2);				// dark green
	Plane* plane_ptr = new Plane(Point3D(0, 0, -50), Normal(0, 0, 1));
	plane_ptr->set_material(matte_ptr3);
	add_object(plane_ptr);

	//int num_samples = 1;
	//int vpWidth = 200;
	//int vpHeight = 200;
	//int pixel_gap = 5;

	//imageWidth = vpWidth * 2 + pixel_gap;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_pixel_size(0.05);
	//vp.set_samples(num_samples);

	////int num_samples = 16;
	////vp.set_sampler(new MultiJittered(num_samples));

	//float vpd = 100;  // view plane distance for 200 x 200 pixel images
	//Pinhole* left_camera_ptr = new Pinhole;
	//left_camera_ptr->set_view_distance(vpd);
	//Pinhole* right_camera_ptr = new Pinhole;
	//right_camera_ptr->set_view_distance(vpd);

	//
	//StereoCamera* stereo_ptr = new StereoCamera;
	//stereo_ptr->set_left_camera(left_camera_ptr);
	//stereo_ptr->set_right_camera(right_camera_ptr);
	//stereo_ptr->use_parallel_viewing();
	////	stereo_ptr->use_transverse_viewing();
	//stereo_ptr->set_pixel_gap(pixel_gap);       // in pixels
	//stereo_ptr->set_eye(5, 0, 100);
	//stereo_ptr->set_lookat(0);
	//stereo_ptr->compute_uvw();
	//stereo_ptr->set_stereo_angle(0.75);  // in degrees
	//stereo_ptr->setup_cameras();
	//set_camera(stereo_ptr);

	//

	///*
	//Spherical* spherical_ptr = new Spherical;
	//spherical_ptr->set_eye(0, 0, 100);
	//spherical_ptr->set_lookat(0, 0, 0);
	//spherical_ptr->set_horizontal_fov(90);
	//spherical_ptr->set_vertical_fov(180);
	//spherical_ptr->compute_uvw();
	//set_camera(spherical_ptr);
	//*/

	///*
	//FishEye* fisheye_ptr = new FishEye();
	//fisheye_ptr->set_eye(0, 0, 100);
	//fisheye_ptr->set_lookat(0, 0, 0);
	//fisheye_ptr->set_fov(90);
	//fisheye_ptr->compute_uvw();
	//set_camera(fisheye_ptr);
	//*/

	///*
	//ThinLens* thin_lens_ptr = new ThinLens;
	//thin_lens_ptr->set_sampler(new MultiJittered(num_samples));
	//thin_lens_ptr->set_eye(20, 0, 30);
	//thin_lens_ptr->set_lookat(0, 0, 0);
	//thin_lens_ptr->set_view_distance(50.0);
	//thin_lens_ptr->set_focal_distance(20.0);
	//thin_lens_ptr->set_lens_radius(3.0);     
	//thin_lens_ptr->compute_uvw();
	//set_camera(thin_lens_ptr);
	//*/

	///*
	//Pinhole* pinhole_ptr = new Pinhole();
	//pinhole_ptr->set_eye(100, 0, 100);
	//pinhole_ptr->set_lookat(0, 0, 0);
	//pinhole_ptr->set_view_distance(50);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);
	//*/


	//background_color = black;
	//tracer_ptr = new MultipleObjects(this);

	//// use access functions to set center and radius for this sphere

	////Sphere* sphere_ptr = new Sphere;
	////sphere_ptr->set_center(0, 0, 20);
	////sphere_ptr->set_radius(20.0);
	////sphere_ptr->set_color(1, 0, 0);  // red
	////add_object(sphere_ptr);
	//
	////sphere_ptr = new Sphere();
	////sphere_ptr->set_center(0, 0, -80);
	////sphere_ptr->set_radius(80.0f);
	////sphere_ptr->set_color(1, 1, 0);	// yellow
	////add_object(sphere_ptr);

	////Plane* plane_ptr = new Plane(Point3D(0, 0, -100), Normal(0, 0, 1));
	////plane_ptr->set_color(0.0, 0.25, 0.0);	// dark green 
	////add_object(plane_ptr);

	//Sphere* sphere1 = new Sphere(Point3D(0, 0, 35), 0.75);
	//sphere1->set_color(0.5, 0, 0);
	//add_object(sphere1);

	//Sphere* sphere2 = new Sphere(Point3D(0), 2);
	//sphere2->set_color(0, 0.5, 0);
	//add_object(sphere2);

	//Sphere* sphere3 = new Sphere(Point3D(1.5, 0, -80), 2);
	//sphere3->set_color(0, 0, 0.5);
	//add_object(sphere3);
}


