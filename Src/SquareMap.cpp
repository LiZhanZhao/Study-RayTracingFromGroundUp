#include "SquareMap.h"

SquareMap::SquareMap(void) {}

SquareMap::SquareMap(const SquareMap& sm) {}

SquareMap&
SquareMap::operator= (const SquareMap& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}

SquareMap::~SquareMap(void) {}

SquareMap*
SquareMap::clone(void) const {
	return (new SquareMap(*this));
}

void
SquareMap::get_texel_coordinates(const 	Point3D& 	local_hit_point,
	const 	int 		xres,
	const 	int 		yres,
	int& 		row,
	int& 		column) const {

	// this is only work for Rectangle£¬because Rectangle set p0(-1, 0, -1)£¬a(0, 0, 2), b(2, 0, 0), default
	float u = (local_hit_point.z + 1) / 2;
	float v = (local_hit_point.x + 1) / 2;

	column = (int)((xres - 1) * u);
	row = (int)((yres - 1) * v);
}
