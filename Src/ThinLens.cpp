#include"ThinLens.h"

void ThinLens::set_sampler(Sampler* sp) {

	if (sampler_ptr != NULL) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	sampler_ptr = sp;
	sampler_ptr->map_samples_to_unit_disk();
}

Vector3D ThinLens::ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const {
	Point2D p(pixel_point.x * f / d, pixel_point.y * f / d);   // hit point on focal plane
	// view coord to world coord
	Vector3D dir = (p.x - lens_point.x) * u + (p.y - lens_point.y) * v - f * w;
	dir.normalize();

	return (dir);
}

void ThinLens::render_scene(const World& w) {
	RGBColor	L;
	Ray			ray;
	ViewPlane	vp(w.vp);
	int 		depth = 0;

	Point2D sp;			// sample point in [0, 1] X [0, 1]
	Point2D pp;			// sample point on a pixel
	Point2D dp; 		// sample point on unit disk
	Point2D lp;			// sample point on lens

	//w.open_window(vp.hres, vp.vres);
	vp.s /= zoom;

	for (int r = 0; r < vp.vres; r++)			// up
	for (int c = 0; c < vp.hres; c++) {		// across 
		L = black;

		for (int n = 0; n < vp.num_samples; n++) {
			sp = vp.sampler_ptr->sample_unit_square();
			pp.x = vp.s * (c - vp.hres / 2.0 + sp.x);
			pp.y = vp.s * (r - vp.vres / 2.0 + sp.y);

			dp = sampler_ptr->sample_unit_disk();
			lp = dp * lens_radius;

			ray.o = eye + lp.x * u + lp.y * v;
			ray.d = ray_direction(pp, lp);
			//L += w.tracer_ptr->trace_ray(ray, depth);
			L += w.tracer_ptr->trace_ray(ray);
		}

		L /= vp.num_samples;
		L *= exposure_time;
		w.display_pixel(r, c, L);
	}
}

ThinLens::ThinLens()
: Camera(), d(500), f(600), lens_radius(1), zoom(1.0), sampler_ptr(NULL)
{}

ThinLens::ThinLens(const ThinLens& ph)
: Camera(ph), d(ph.d), f(ph.f), lens_radius(ph.lens_radius), zoom(ph.zoom), 
	sampler_ptr(ph.sampler_ptr)
{}

Camera* ThinLens::clone(void) const {
	return (new ThinLens(*this));
}
