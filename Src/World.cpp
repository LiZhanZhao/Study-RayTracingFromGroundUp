// this file contains the definition of the World class

#include "World.h"
#include "Constants.h"

// geometric objects

#include "Plane.h"
#include "Sphere.h"

// tracers

//#include "SingleSphere.h"
//#include "MultipleObjects.h"
#include "RayCast.h"

// cameras
#include "Pinhole.h"
#include "ThinLens.h"
#include "Fisheye.h"
#include "Spherical.h"
#include "StereoCamera.h"

// utilities

#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"



// build functions

//#include "BuildFigure.cpp"
#include "BuildFigure.cpp"


// -------------------------------------------------------------------- default constructor

// tracer_ptr is set to NULL because the build functions will always construct the appropriate tracer
// ambient_ptr is set to a default ambient light because this will do for most scenes
// camera_ptr is set to NULL because the build functions will always have to construct a camera
// and set its parameters

World::World(void)
	:  	background_color(black),
	tracer_ptr(NULL), imageBuffer(NULL), camera_ptr(NULL)
{
	ambient_ptr = new Ambient();
}



//------------------------------------------------------------------ destructor

World::~World(void) {	
	
	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}
	/*if (buffer){
		for (int i = 0; i < vp.hres * vp.vres; i++){
			delete &(buffer[i]);
		}
		delete buffer;
	}*/

	delete_objects();				
	delete_lights();
}

// ------------------------------------------------------------------ clamp

RGBColor
World::max_to_one(const RGBColor& c) const  {
	float max_value = max(c.r, max(c.g, c.b));
	
	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}


// ------------------------------------------------------------------ clamp_to_color
// Set color to red if any component is greater than one

RGBColor
World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}
		
	return (c);
}


// ---------------------------------------------------------------------------display_pixel
// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function


void
World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);
	
	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);
	
   //have to start from max y coordinate to convert to screen coordinates
   int x = column;
   int y = imageHeight - row - 1;
   
   int index = y * imageWidth + x - 1;
   imageBuffer[index] = mapped_color;
}

// ----------------------------------------------------------------------------- hit_objects
ShadeRec
World::hit_objects(const Ray& ray) {

	ShadeRec	sr(*this);
	double		t;
	Normal normal;
	Point3D local_hit_point;
	double		tmin = kHugeValue;
	int 		num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
	if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
		sr.hit_an_object = true;
		tmin = t;
		sr.material_ptr = objects[j]->get_material();
		sr.hit_point = ray.o + t * ray.d;
		normal = sr.normal;
		local_hit_point = sr.local_hit_point;
	}

	if (sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
		
	}

	return(sr);
}

/*
ShadeRec									
World::hit_objects(const Ray& ray) {

	ShadeRec	sr(*this); 
	double		t;
	Normal normal;
	Point3D local_hit_point;
	double		tmin 			= kHugeValue;
	int 		num_objects 	= objects.size();
	RGBColor resColor;
	
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t;

			sr.hit_point 		= ray.o + t * ray.d;
			normal 				= sr.normal;
			local_hit_point	 	= sr.local_hit_point;

			resColor = objects[j]->get_color();
		}
  
	if(sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
		sr.color = resColor;
	}
		
	return(sr);   
}
*/


//------------------------------------------------------------------ delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 

void
World::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase (objects.begin(), objects.end());
}

void World::delete_lights(void){
	int num_lights = lights.size();
	for (int j = 0; j < num_lights; j++){
		delete lights[j];
		lights[j] = NULL;
	}

	lights.erase(lights.begin(), lights.end());
}

bool World::outputPPMImage(string filePath)
{
	FILE *fp = fopen(filePath.c_str(), "wb");
	if (!fp) return false;
	//fprintf(fp, "P6\n%d %d\n255\n", vp.hres, vp.vres);
	fprintf(fp, "P6\n%d %d\n255\n", imageWidth, imageHeight);
	int size = imageWidth * imageHeight;
	// now write out image in binary
	for (int i = 0; i < size; i++){
		unsigned char d[3] = { imageBuffer[i].r * 255, imageBuffer[i].g * 255, imageBuffer[i].b * 255 };
		fwrite(d, 1, 3, fp);

	}
	fclose(fp);
	return true;
}

void World::set_camera(Camera* cam_ptr){
	if (camera_ptr != NULL){
		delete camera_ptr;
	}
	camera_ptr = cam_ptr;
}

void World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}

void World::add_light(Light* light_ptr){
	lights.push_back(light_ptr);
}

void World::set_ambient_light(Light* light_ptr){
	ambient_ptr = light_ptr;
}