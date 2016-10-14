// this file contains the definition of the World class

#include "World.h"
#include "Constants.h"

// geometric objects

#include "Plane.h"
#include "Sphere.h"

// tracers

//#include "SingleSphere.h"
#include "MultipleObjects.h"

// cameras


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
	tracer_ptr(NULL), buffer(NULL)
		
{}



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
}


//------------------------------------------------------------------ render_scene

// This uses orthographic viewing along the zw axis

void World::render_scene(void) {

	RGBColor	pixel_color;	 	
	Ray			ray;					
	int 		hres 	= vp.hres;
	int 		vres 	= vp.vres;
	float		s		= vp.s;
	float		zw		= 100.0;				// hardwired in

	ray.d = Vector3D(0, 0, -1);

	buffer = new RGBColor[vp.vres * vp.hres];
	int n = (int)sqrt(vp.num_samples);
	
	for (int r = 0; r < vres; r++)			// up
		for (int c = 0; c <= hres; c++) {	// across 			

			// not Anti-Aliasing
			//ray.o = Point3D(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw);
			//pixel_color = tracer_ptr->trace_ray(ray);
			//display_pixel(r, c, pixel_color);
			

			pixel_color = black;
			for (int j = 0; j < vp.num_samples; j++){
				Point2D sp = vp.sampler_ptr->sample_unit_square();
				float x = s * (c - hres / 2.0 + sp.x);
				float y = s * (r - vres / 2.0 + sp.y);
				ray.o = Point3D(x, y, zw);
				pixel_color += tracer_ptr->trace_ray(ray);
			}
			
			pixel_color = pixel_color / vp.num_samples;
			display_pixel(r, c, pixel_color);

		}	
}  

void World::render_perspective_scene()
{
	RGBColor pixel_color;
	Ray ray;

	buffer = new RGBColor[vp.vres * vp.hres];

	ray.o = Point3D(0, 0, eye);
	for (int r = 0; r < vp.vres; r++){
		for (int c = 0; c < vp.hres; c++){
			float pixel_x = vp.s * (c - vp.hres / 2.0 + 0.5);
			float pixel_y = vp.s * (r - vp.vres / 2.0 + 0.5);
			//float pixel_z = eye - vp_dist;

			// ray.d = pixel - ray.o
			ray.d = Vector3D(pixel_x, pixel_y, target - eye);
			
			ray.d.normalize();
			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);

		}
	}
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
   int y = vp.vres - row - 1;
   
   int index = y * vp.hres + x - 1;
   buffer[index] = mapped_color;

  /* paintArea->setPixel(x, y, (int)(mapped_color.r * 255),
                             (int)(mapped_color.g * 255),
                             (int)(mapped_color.b * 255));*/
}

// ----------------------------------------------------------------------------- hit_objects

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

bool World::outputPPMImage(string filePath)
{
	FILE *fp = fopen(filePath.c_str(), "wb");
	if (!fp) return false;
	fprintf(fp, "P6\n%d %d\n255\n", vp.hres, vp.vres);
	int size = vp.hres * vp.vres;
	// now write out image in binary
	for (int i = 0; i < size; i++){
		unsigned char d[3] = { buffer[i].r * 255, buffer[i].g * 255, buffer[i].b * 255 };
		fwrite(d, 1, 3, fp);

	}
	fclose(fp);
	return true;
}



