#include "StereoCamera.h"

StereoCamera::StereoCamera()
: Camera(), viewing_type(ViewingType::parallel), pixel_gap(5), beta(1.0f), 
left_camera_ptr(NULL),right_camera_ptr(NULL)
{}

StereoCamera::StereoCamera(const StereoCamera& sc)
: Camera(sc), viewing_type(sc.viewing_type), pixel_gap(sc.pixel_gap), beta(sc.beta),
left_camera_ptr(sc.left_camera_ptr), right_camera_ptr(sc.right_camera_ptr)
{}

Camera* StereoCamera::clone(void) const{
	return (new StereoCamera(*this));
}

void StereoCamera::render_scene(const World& w){
	ViewPlane	vp = w.vp;
	int 		hres = vp.hres;
	int 		vres = vp.vres;

	//w.open_window(2 * hres + pixel_gap, vres);

	double r = eye.distance(lookat);
	double x = r * tan(0.5 * beta * PI_ON_180);

	if (viewing_type == parallel) {
		left_camera_ptr->render_stereo(w, x, 0);						// left view on left
		right_camera_ptr->render_stereo(w, -x, hres + pixel_gap);   	// right view on right
	}

	if (viewing_type == transverse) {
		right_camera_ptr->render_stereo(w, -x, 0);   					// right view on left
		left_camera_ptr->render_stereo(w, x, hres + pixel_gap);    		// left view on right
	}
}


void StereoCamera::setup_cameras(void){
	double r = eye.distance(lookat);
	double x = r * tan(0.5 * beta * PI_ON_180);  //  half the camera separation distance

	left_camera_ptr->set_eye(eye - x * u); // x * u is view coord to world coord 
	left_camera_ptr->set_lookat(lookat - x * u);
	left_camera_ptr->compute_uvw();

	right_camera_ptr->set_eye(eye + x * u);
	right_camera_ptr->set_lookat(lookat + x * u);
	right_camera_ptr->compute_uvw();
}