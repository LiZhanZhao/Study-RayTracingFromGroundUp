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
#include "SV_Matte.h"

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

//Texture
#include "ImageTexture.h"
#include "Checker3D.h"
#include "PlaneChecker.h"
#include "TInstance.h"

// Mapping
#include "SphericalMap.h"
#include "SquareMap.h"

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

	tracer_ptr = new RayCast(this);
	background_color = RGBColor(0.5);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 100);
	pinhole_ptr->set_lookat(0.0);
	pinhole_ptr->set_view_distance(7500.0);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0, 0, 1);
	light_ptr->scale_radiance(3.0);
	add_light(light_ptr);

	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(0.3);
	checker_ptr->set_color1(white);
	checker_ptr->set_color2(black);

	TInstance* scaled_checker_ptr = new TInstance(checker_ptr);
	//scaled_checker_ptr->scale(2, 1, 1);

	SV_Matte* sv_matte_ptr = new SV_Matte;
	sv_matte_ptr->set_ka(0.8);
	sv_matte_ptr->set_kd(0.4);
	sv_matte_ptr->set_cd(scaled_checker_ptr);

	Box* box_ptr = new Box(Point3D(-1.0), Point3D(1.0));
	box_ptr->set_material(sv_matte_ptr);

	Instance* transformed_box_ptr = new Instance(box_ptr);
	transformed_box_ptr->scale(2, 1, 1);
	transformed_box_ptr->rotate_z(45);
	add_object(transformed_box_ptr);




	//int vpWidth = 904;
	//int vpHeight = 300;
	//int num_samples = 16;

	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);

	//tracer_ptr = new RayCast(this);
	//background_color = RGBColor(0.75);

	//Ambient* ambient_ptr = new Ambient;
	//ambient_ptr->scale_radiance(0.5);
	//set_ambient_light(ambient_ptr);


	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(0, 0, 200);
	//pinhole_ptr->set_lookat(0.0);
	//pinhole_ptr->set_view_distance(9600.0);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);


	//PointLight* light_ptr = new PointLight;
	//light_ptr->set_location(50, 100, 100);
	//light_ptr->scale_radiance(4.0);
	//light_ptr->set_shadows(false);
	//add_light(light_ptr);


	//// the spheres

	//Checker3D* checker_ptr = new Checker3D;
	//checker_ptr->set_size(1.0);
	//checker_ptr->set_color1(black);
	//checker_ptr->set_color2(white);


	//double radius;

	//// sphere 1

	//TInstance* transformed_checker_ptr1 = new TInstance(checker_ptr);
	//transformed_checker_ptr1->translate(0.5, 0.5, 0.0);

	//SV_Matte* sv_matte_ptr1 = new SV_Matte;
	//sv_matte_ptr1->set_ka(0.5);
	//sv_matte_ptr1->set_kd(0.75);
	//sv_matte_ptr1->set_cd(transformed_checker_ptr1);

	//radius = 3.0;
	//Instance* sphere_ptr1 = new Instance(new Sphere(Point3D(0.0), radius));
	//sphere_ptr1->set_material(sv_matte_ptr1);
	//sphere_ptr1->translate(-6.25, 0.0, 0.0);
	//add_object(sphere_ptr1);


	//// sphere 2

	//TInstance* transformed_checker_ptr2 = new TInstance(checker_ptr);
	//transformed_checker_ptr2->scale(0.75);
	//transformed_checker_ptr2->translate(0.375, 0.375, 0.0);

	//SV_Matte* sv_matte_ptr2 = new SV_Matte;
	//sv_matte_ptr2->set_ka(0.5);
	//sv_matte_ptr2->set_kd(0.75);
	//sv_matte_ptr2->set_cd(transformed_checker_ptr2);

	//radius = 2.25;
	//Instance* sphere_ptr2 = new Instance(new Sphere(Point3D(0.0), radius));
	//sphere_ptr2->set_material(sv_matte_ptr2);
	//sphere_ptr2->translate(-1.0, 0.0, 0.0);
	//add_object(sphere_ptr2);


	//// sphere 3

	//TInstance* transformed_checker_ptr3 = new TInstance(checker_ptr);
	//transformed_checker_ptr3->scale(0.5833333);
	//transformed_checker_ptr3->translate(0.29166, 0.29166, 0.0);

	//SV_Matte* sv_matte_ptr3 = new SV_Matte;
	//sv_matte_ptr3->set_ka(0.5);
	//sv_matte_ptr3->set_kd(0.75);
	//sv_matte_ptr3->set_cd(transformed_checker_ptr3);

	//radius = 1.75;
	//Instance* sphere_ptr3 = new Instance(new Sphere(Point3D(0.0), radius));
	//sphere_ptr3->set_material(sv_matte_ptr3);
	//sphere_ptr3->translate(3.0, 0.0, 0.0);
	//add_object(sphere_ptr3);


	//// sphere 4

	//TInstance* transformed_checker_ptr4 = new TInstance(checker_ptr);
	//transformed_checker_ptr4->scale(0.3333333);
	//transformed_checker_ptr4->translate(0.166666, 0.166666, 0.0);

	//SV_Matte* sv_matte_ptr4 = new SV_Matte;
	//sv_matte_ptr4->set_ka(0.5);
	//sv_matte_ptr4->set_kd(0.75);
	//sv_matte_ptr4->set_cd(transformed_checker_ptr4);

	//radius = 1.0;
	//Instance* sphere_ptr4 = new Instance(new Sphere(Point3D(0.0), radius));
	//sphere_ptr4->set_material(sv_matte_ptr4);
	//sphere_ptr4->translate(5.75, 0.0, 0.0);
	//add_object(sphere_ptr4);


	//// sphere 5

	//TInstance* transformed_checker_ptr5 = new TInstance(checker_ptr);
	//transformed_checker_ptr5->scale(0.25);
	//transformed_checker_ptr5->translate(0.125, 0.125, 0.0);

	//SV_Matte* sv_matte_ptr5 = new SV_Matte;
	//sv_matte_ptr5->set_ka(0.5);
	//sv_matte_ptr5->set_kd(0.75);
	//sv_matte_ptr5->set_cd(transformed_checker_ptr5);

	//radius = 0.75;
	//Instance* sphere_ptr5 = new Instance(new Sphere(Point3D(0.0), radius));
	//sphere_ptr5->set_material(sv_matte_ptr5);
	//sphere_ptr5->translate(7.5, 0.0, 0.0);
	//add_object(sphere_ptr5);


	//// sphere 6

	//TInstance* transformed_checker_ptr6 = new TInstance(checker_ptr);
	//transformed_checker_ptr6->scale(0.166666);
	//transformed_checker_ptr6->translate(0.083333, 0.083333, 0.0);

	//SV_Matte* sv_matte_ptr6 = new SV_Matte;
	//sv_matte_ptr6->set_ka(0.5);
	//sv_matte_ptr6->set_kd(0.75);
	//sv_matte_ptr6->set_cd(transformed_checker_ptr6);

	//radius = 0.5;
	//Instance* sphere_ptr6 = new Instance(new Sphere(Point3D(0.0), radius));
	//sphere_ptr6->set_material(sv_matte_ptr6);
	//sphere_ptr6->translate(8.75, 0.0, 0.0);
	//add_object(sphere_ptr6);








	//int vpWidth = 880;
	//int vpHeight = 300;
	//int num_samples = 16;
	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);

	//tracer_ptr = new RayCast(this);
	//background_color = RGBColor(0.5);

	//Pinhole* pinholePtr = new Pinhole;
	//pinholePtr->set_eye(100, 100, 300);
	//pinholePtr->set_lookat(-0.2, 1.0, 0);
	//pinholePtr->set_view_distance(12000.0);
	//pinholePtr->compute_uvw();
	//set_camera(pinholePtr);

	//Directional* light_ptr = new Directional;
	//light_ptr->set_direction(0, 0, 1);
	//light_ptr->scale_radiance(1.5);
	//add_light(light_ptr);


	//// ground plane

	//PlaneChecker* plane_checker_ptr = new PlaneChecker;
	//plane_checker_ptr->set_size(1.5);
	////plane_checker_ptr->set_outline_width(1.4);
	//plane_checker_ptr->set_outline_width(0.1);
	//plane_checker_ptr->set_color1(0.35);
	//plane_checker_ptr->set_color2(0.5);
	//plane_checker_ptr->set_outline_color(RGBColor(1.0f, 1.0f, 0.0f));

	//SV_Matte* sv_matte_ptr8 = new SV_Matte;
	//sv_matte_ptr8->set_ka(0.75);
	//sv_matte_ptr8->set_kd(0.75);
	//sv_matte_ptr8->set_cd(plane_checker_ptr);

	//Instance* plane_ptr = new Instance(new Plane); // a generic plane is the (x, z) plane
	//plane_ptr->set_material(sv_matte_ptr8);
	//plane_ptr->translate(0, -4.5, 0);
	//add_object(plane_ptr);


	

	//int vpWidth = 400;
	//int vpHeight = 400;
	//int num_samples = 16;
	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);

	//tracer_ptr = new RayCast(this);

	//background_color = black;

	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(11, 5, 9);
	//pinhole_ptr->set_view_distance(1600.0);
	//pinhole_ptr->set_lookat(0, -0.5, 0);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);


	//Directional* directional_ptr = new Directional;
	//directional_ptr->set_direction(0.75, 1, -0.15);
	//directional_ptr->scale_radiance(4.5);
	//directional_ptr->set_shadows(true);
	//add_light(directional_ptr);

	//Image* image_ptr = new Image;
	//image_ptr->read_ppm_file("Texture/BlueGlass.ppm");

	//ImageTexture* texture_ptr = new ImageTexture;
	//texture_ptr->set_image(image_ptr);

	//SV_Matte* sv_matte_ptr = new SV_Matte;
	//sv_matte_ptr->set_ka(0.1);
	//sv_matte_ptr->set_kd(0.75);
	//sv_matte_ptr->set_cd(texture_ptr);

	//char* file_name = "Ply/TwoUVTriangles.ply";
	//Grid* grid_ptr = new Grid(new Mesh);
	//grid_ptr->read_flat_uv_triangles(file_name);		// for Figure 29.22(a)
	////grid_ptr->read_smooth_uv_triangles(file_name);		// for Figure 29.22(b)
	//grid_ptr->set_material(sv_matte_ptr);
	//grid_ptr->setup_cells();
	//add_object(grid_ptr);


	//Matte* matte_ptr = new Matte;
	//matte_ptr->set_cd(1, 0.9, 0.6);
	//matte_ptr->set_ka(0.25);
	//matte_ptr->set_kd(0.4);

	//Plane* plane_ptr1 = new Plane(Point3D(0, -2.0, 0), Normal(0, 1, 0));
	//plane_ptr1->set_material(matte_ptr);
	//add_object(plane_ptr1);







	//int vpWidth = 400;
	//int vpHeight = 400;
	//int num_samples = 16;

	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);
	//vp.set_max_depth(0);

	//background_color = RGBColor(0.0);

	//tracer_ptr = new RayCast(this);

	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(5, 1.5, 8);
	//pinhole_ptr->set_lookat(0.25, 0.0, 0.0);
	//pinhole_ptr->set_view_distance(1000.0);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);

	//Directional* light_ptr = new Directional;
	//light_ptr->set_direction(-15, 20, 25);
	//light_ptr->scale_radiance(2.5);
	//light_ptr->set_shadows(true);
	//add_light(light_ptr);

	//// image:

	//Image* image_ptr = new Image;
	//image_ptr->read_ppm_file("Texture/Lightlace.ppm");

	//// mapping:

	//SquareMap* map_ptr = new SquareMap;

	//// image texture:

	//ImageTexture* texture_ptr = new ImageTexture(image_ptr);
	//texture_ptr->set_mapping(map_ptr);

	//// spatially varying material:

	//SV_Matte* sv_matte_ptr = new SV_Matte;
	//sv_matte_ptr->set_ka(0.40);
	//sv_matte_ptr->set_kd(0.95);
	//sv_matte_ptr->set_cd(texture_ptr);

	//// generic rectangle:

	//Rectangle* rectangle_ptr = new Rectangle;
	//rectangle_ptr->set_material(sv_matte_ptr);

	//// transformed rectangle:

	//Instance* lightlace_ptr = new Instance(rectangle_ptr);
	//lightlace_ptr->scale(1.0, 1.0, 1.5);
	//lightlace_ptr->rotate_z(90);
	//lightlace_ptr->rotate_y(90);
	//add_object(lightlace_ptr);

	//// ground plane

	//Matte* matte_ptr1 = new Matte;
	//matte_ptr1->set_ka(0.25);
	//matte_ptr1->set_kd(0.5);
	//matte_ptr1->set_cd(1.0);

	//Plane* plane_ptr = new Plane(Point3D(0.0, -1.0, 0.0), Normal(0.0, 1.0, 0.0));
	//plane_ptr->set_material(matte_ptr1);
	//add_object(plane_ptr);






	//int vpWidth = 700;
	//int vpHeight = 700;
	//int num_samples = 16;

	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);

	//background_color = black;

	//tracer_ptr = new RayCast(this);

	//Pinhole* camera_ptr = new Pinhole;
	//camera_ptr->set_eye(0, 0, 65);
	//camera_ptr->set_lookat(0.0);
	//camera_ptr->set_view_distance(21000.0);
	//camera_ptr->compute_uvw();
	//set_camera(camera_ptr);


	//Directional* light_ptr = new Directional;
	//light_ptr->set_direction(-0.25, 0.4, 1);
	//light_ptr->scale_radiance(2.5);
	//add_light(light_ptr);


	//// image:					

	//Image* image_ptr = new Image;
	////	image_ptr->read_ppm_file("EarthLowRes.ppm");
	//image_ptr->read_ppm_file("Texture/EarthHighRes.ppm");


	//// mapping:

	//SphericalMap* map_ptr = new SphericalMap;


	//// image based texture:  

	//ImageTexture* texture_ptr = new ImageTexture;
	//texture_ptr->set_image(image_ptr);
	//texture_ptr->set_mapping(map_ptr);


	//// textured material:

	//SV_Matte* sv_matte_ptr = new SV_Matte;
	//sv_matte_ptr->set_ka(0.2);
	//sv_matte_ptr->set_kd(0.8);
	//sv_matte_ptr->set_cd(texture_ptr);


	//// generic sphere:

	//Sphere*	sphere_ptr = new Sphere;
	//sphere_ptr->set_material(sv_matte_ptr);


	//// rotated sphere

	//Instance* earth_ptr = new Instance(sphere_ptr);
	//earth_ptr->rotate_y(60);
	//add_object(earth_ptr);




	//int vpWidth = 600;
	//int vpHeight = 400;
	//int num_samples = 9;
	//imageWidth = vpWidth;
	//imageHeight = vpHeight;
	//imageBuffer = new RGBColor[imageWidth * imageHeight];

	//vp.set_hres(vpWidth);
	//vp.set_vres(vpHeight);
	//vp.set_samples(num_samples);
	////vp.set_max_depth(15);
	//vp.set_max_depth(11);

	//tracer_ptr = new Whitted(this);

	//background_color = RGBColor(0.75);

	//Ambient* ambient_ptr = new Ambient;
	//ambient_ptr->scale_radiance(1.0);
	//set_ambient_light(ambient_ptr);


	//Pinhole* pinhole_ptr = new Pinhole;
	//pinhole_ptr->set_eye(10, 12, 20);
	//pinhole_ptr->set_lookat(-3.75, 3, 0);
	//pinhole_ptr->set_view_distance(1500.0);
	//pinhole_ptr->compute_uvw();
	//set_camera(pinhole_ptr);

	//PointLight* light_ptr1 = new PointLight;
	//light_ptr1->set_location(20, 25, -20);
	//light_ptr1->scale_radiance(3.0);
	//light_ptr1->set_shadows(true);
	//add_light(light_ptr1);


	//float c = 1.75;  // this allows us to adjust the filter color without changing the hue
	//RGBColor glass_color(0.27*c, 0.49*c, 0.42*c);


	//Dielectric* glass_ptr = new Dielectric;
	//glass_ptr->set_eta_in(1.50);		// glass
	//glass_ptr->set_eta_out(1.0);		// air
	//glass_ptr->set_cf_in(glass_color);
	//glass_ptr->set_cf_out(white);

	//double 	thickness = 0.25;
	//double 	height = 4.0;
	//double 	delta = 1.0;			// length change of each box

	//int 	num_boxes = 10;
	//double 	x_min = -10.0;		// where the boxes start in the x direction
	//double 	gap = 0.5;   		// gap between the boxes

	//for (int j = 0; j < num_boxes; j++) {
	//	double length = thickness + j * delta;
	//	Point3D p0(x_min + j * (thickness + gap), 0.0, -length);
	//	Point3D p1(x_min + j * (thickness + gap) + thickness, height, 0.0);

	//	Box* box_ptr = new Box(p0, p1);
	//	box_ptr->set_material(glass_ptr);
	//	add_object(box_ptr);
	//}


	//// plane

	//Matte* matte_ptr = new Matte;
	//matte_ptr->set_ka(0.5);
	//matte_ptr->set_kd(0.65);
	//matte_ptr->set_cd(0.75);

	//Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0));
	//plane_ptr->set_material(matte_ptr);
	//add_object(plane_ptr);

}


