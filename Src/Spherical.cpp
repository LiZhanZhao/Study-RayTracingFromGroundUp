#include "Spherical.h"

Vector3D Spherical::ray_direction(const Point2D& 	pp,
const int 		hres,
const int 		vres,
const float 	s) const {

	// compute the normalised device coordinates

	Point2D pn(2.0 / (s * hres) * pp.x, 2.0 / (s * vres) * pp.y);

	// compute the angles lambda and phi in radians

	float lambda = pn.x * lambda_max * PI_ON_180;
	float psi = pn.y * psi_max * PI_ON_180;

	// compute the regular azimuth and polar angles

	float phi = PI - lambda;
	float theta = 0.5 * PI - psi;

	float sin_phi = sin(phi);
	float cos_phi = cos(phi);
	float sin_theta = sin(theta);
	float cos_theta = cos(theta);

	Vector3D dir = sin_theta * sin_phi * u + cos_theta * v + sin_theta * cos_phi * w;

	return (dir);
}

void Spherical::render_scene(const World& wr) {
	RGBColor	L;
	ViewPlane	vp(wr.vp);
	int 		hres = vp.hres;
	int 		vres = vp.vres;
	float		s = vp.s;
	Ray			ray;
	int 		depth = 0;
	Point2D 	sp; 					// sample point in [0, 1] X [0, 1]
	Point2D 	pp;						// sample point on the pixel

	//wr.open_window(vp.hres, vp.vres);
	ray.o = eye;

	for (int r = 0; r < vres; r++)		// up
	for (int c = 0; c < hres; c++) {	// across 					
		L = black;

		for (int j = 0; j < vp.num_samples; j++) {
			sp = vp.sampler_ptr->sample_unit_square();
			pp.x = s * (c - 0.5 * hres + sp.x);
			pp.y = s * (r - 0.5 * vres + sp.y);
			ray.d = ray_direction(pp, hres, vres, s);

			L += wr.tracer_ptr->trace_ray(ray);
			//L += wr.tracer_ptr->trace_ray(ray, depth);
		}

		L /= vp.num_samples;
		L *= exposure_time;
		wr.display_pixel(r, c, L);
	}
}

Spherical::Spherical()
: Camera(), psi_max(90), lambda_max(180)
{
}

Spherical::Spherical(const Spherical& s)
: Camera(s), psi_max(s.psi_max), lambda_max(s.lambda_max)
{}

Camera* Spherical::clone(void) const {
	return (new Spherical(*this));
}