#ifndef __THINLENS__
#define __THINLENS__

#include "Point2D.h"
#include "World.h"    // we can #include "World.h" here
#include "Camera.h"

class ThinLens: public Camera {

	public:
	
		// constructors, access functions, etc
		ThinLens();
		ThinLens(const ThinLens& ph);
		
		void set_sampler(Sampler* sp);	
		
		Vector3D ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const;
		
		virtual void render_scene(const World& w);

		virtual Camera* clone(void) const;

		void set_view_distance(const float vpd);

		void set_zoom(float zoom_factor);
		
		void set_lens_radius(float len_radius);

		void set_focal_distance(float dist);

	private:
	
		float		lens_radius;	// lens radius
		float		d;				// view plane distance
		float		f;				// focal distance
		float		zoom;			// zoom factor
		Sampler*	sampler_ptr;	// sampler object
};


inline void ThinLens::set_view_distance(float _d) {
	d = _d;
}

inline void ThinLens::set_zoom(float zoom_factor) {
	zoom = zoom_factor;
}

inline void ThinLens::set_lens_radius(float lr)
{
	lens_radius = lr;
}

inline void ThinLens::set_focal_distance(float dist){
	f = dist;
}

#endif