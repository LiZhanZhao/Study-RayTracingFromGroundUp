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

// Mapping
#include "SphericalMap.h"

void World::build(void) {

	int vpWidth = 700;
	int vpHeight = 700;
	int num_samples = 16;

	imageWidth = vpWidth;
	imageHeight = vpHeight;
	imageBuffer = new RGBColor[imageWidth * imageHeight];

	vp.set_hres(vpWidth);
	vp.set_vres(vpHeight);
	vp.set_samples(num_samples);

	background_color = black;

	tracer_ptr = new RayCast(this);

	Pinhole* camera_ptr = new Pinhole;
	camera_ptr->set_eye(0, 0, 65);
	camera_ptr->set_lookat(0.0);
	camera_ptr->set_view_distance(21000.0);
	camera_ptr->compute_uvw();
	set_camera(camera_ptr);


	Directional* light_ptr = new Directional;
	light_ptr->set_direction(-0.25, 0.4, 1);
	light_ptr->scale_radiance(2.5);
	add_light(light_ptr);


	// image:					

	Image* image_ptr = new Image;
	//	image_ptr->read_ppm_file("EarthLowRes.ppm");
	image_ptr->read_ppm_file("Texture/EarthHighRes.ppm");


	// mapping:

	SphericalMap* map_ptr = new SphericalMap;


	// image based texture:  

	ImageTexture* texture_ptr = new ImageTexture;
	texture_ptr->set_image(image_ptr);
	texture_ptr->set_mapping(map_ptr);


	// textured material:

	SV_Matte* sv_matte_ptr = new SV_Matte;
	sv_matte_ptr->set_ka(0.2);
	sv_matte_ptr->set_kd(0.8);
	sv_matte_ptr->set_cd(texture_ptr);


	// generic sphere:

	Sphere*	sphere_ptr = new Sphere;
	sphere_ptr->set_material(sv_matte_ptr);


	// rotated sphere

	Instance* earth_ptr = new Instance(sphere_ptr);
	earth_ptr->rotate_y(60);
	add_object(earth_ptr);




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


