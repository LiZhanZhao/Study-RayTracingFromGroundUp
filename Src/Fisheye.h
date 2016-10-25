#ifndef __FISHEYE__
#define __FISHEYE__

#include "Point2D.h"
#include "World.h"    // we can #include "World.h" here
#include "Camera.h"

class FishEye: public Camera {			
	public:
		// constructors, etc
		Vector3D ray_direction(	const Point2D& pp, 
						const int 	hres, 
						const int 	vres, 
						const float s, 
						float& 		r_squared) const;

		virtual void render_scene(const World& w);

		void set_fov(float fov);
		virtual Camera* clone(void) const;
		FishEye();
		FishEye(const FishEye& fe);
	private:
		float psi_max;	// in degrees
};


inline void FishEye::set_fov(float fov){
	psi_max = fov;
}

#endif

