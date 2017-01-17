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
#include "FBmTexture.h"
#include "TurbulenceTexture.h"
#include "WrappedFBmTexture.h"
#include "RampFBmTexture.h"

// Mapping
#include "SphericalMap.h"
#include "SquareMap.h"

// Noise
#include "CubicNoise.h"

void World::build(void) {
	int vpWidth = 600;
	int vpHeight = 600;
	int num_samples = 16;

	imageWidth = vpWidth;
	imageHeight = vpHeight;
	imageBuffer = new RGBColor[imageWidth * imageHeight];

	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);

	background_color = black;
	tracer_ptr = new RayCast(this);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 100);
	pinhole_ptr->set_lookat(0.0);
	pinhole_ptr->set_view_distance(5800.0);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);


	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(20, 20, 40);
	light_ptr->scale_radiance(2.5);
	add_light(light_ptr);


	// noise:

	CubicNoise* noise_ptr = new CubicNoise;
	noise_ptr->set_num_octaves(6);
	noise_ptr->set_gain(0.5);
	noise_ptr->set_lacunarity(2.0);

	// ramp image:

	Image* image_ptr = new Image;
	image_ptr->read_ppm_file("Texture/BlueMarbleRamp.ppm");

	// marble texture:	

	RampFBmTexture* marble_ptr = new RampFBmTexture(image_ptr);
	marble_ptr->set_noise(noise_ptr);
	//marble_ptr->set_perturbation(4.0);		// for Figure 31.33(a)
		marble_ptr->set_perturbation(8.0);		// for Figure 31.33(b)
	//	marble_ptr->set_perturbation(30.0);		// for Figure 31.33(c)

	// material:

	SV_Matte* sv_matte_ptr = new SV_Matte;
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.9);
	sv_matte_ptr->set_cd(marble_ptr);


	Instance* sphere_ptr1 = new Instance(new Sphere(Point3D(0.0), 5.0));
	sphere_ptr1->set_material(sv_matte_ptr);
	sphere_ptr1->rotate_y(180);
	add_object(sphere_ptr1);






	

}


