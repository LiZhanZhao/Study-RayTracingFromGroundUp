#ifndef __STEREOCAMERA__
#define __STEREOCAMERA__

typedef enum {
	parallel,
	transverse
} ViewingType;

#include "Camera.h"
#include "Point2D.h"
#include "World.h"    // we can #include "World.h" here

class StereoCamera : public Camera {
public:

	// constructors, etc.
	StereoCamera();
	StereoCamera(const StereoCamera& fe);
	virtual Camera* clone(void) const;

	virtual void render_scene(const World& w);

	void set_left_camera(Camera* cam_ptr);
	void set_right_camera(Camera* camera_ptr);
	void use_parallel_viewing();
	void use_transverse_viewing();
	void set_pixel_gap(int gap);
	void set_stereo_angle(float angle);
	void setup_cameras(void);
private:

	ViewingType	viewing_type;		// parallel or transverse viewing
	int			pixel_gap;			// gap in pixels between the left and right images
	float		beta;				// stereo separation angle	
	Camera*		left_camera_ptr;	// left eye camera
	Camera*		right_camera_ptr;	// right eye camera
};

inline void StereoCamera::set_left_camera(Camera* cam_ptr){
	left_camera_ptr = cam_ptr;
}

inline void StereoCamera::set_right_camera(Camera* cam_ptr){
	right_camera_ptr = cam_ptr;
}

inline void StereoCamera::use_parallel_viewing(){
	viewing_type = ViewingType::parallel;
}

inline void StereoCamera::use_transverse_viewing(){
	viewing_type = ViewingType::transverse;
}

inline void StereoCamera::set_pixel_gap(int gap){
	pixel_gap = gap;
}

inline void StereoCamera::set_stereo_angle(float angle){
	beta = angle;
}

#endif