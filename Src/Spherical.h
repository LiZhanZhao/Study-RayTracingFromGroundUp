#ifndef __SPHERICAL__
#define __SPHERICAL__

#include "Point2D.h"
#include "World.h"    // we can #include "World.h" here
#include "Camera.h"

class Spherical : public Camera {
public:
	// constructors, etc
	Vector3D ray_direction(const Point2D& pp,
		const int 	hres,
		const int 	vres,
		const float s
		) const;

	virtual void render_scene(const World& w);

	void set_horizontal_fov(float fov);
	void set_vertical_fov(float fov);

	virtual Camera* clone(void) const;
	Spherical();
	Spherical(const Spherical& fe);
private:
	float psi_max;	// in degrees
	float lambda_max; // in degrees
};


inline void Spherical::set_horizontal_fov(float fov){
	lambda_max = fov;
}

inline void Spherical::set_vertical_fov(float fov){
	psi_max = fov;

}

#endif