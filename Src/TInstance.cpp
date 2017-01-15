#include "TInstance.h"

TInstance::TInstance(void)
: Texture(), texture_ptr(NULL), inv_matrix()
{
}

TInstance::TInstance(Texture* tex)
: Texture(), inv_matrix()
{
	texture_ptr = tex;
}

TInstance::TInstance(const TInstance& it)
: Texture(it), texture_ptr(it.texture_ptr), inv_matrix(it.inv_matrix)

{
}

TInstance* TInstance::clone(void) const{
	return (new TInstance(*this));
}

TInstance::~TInstance(void){
}

TInstance&
TInstance::operator= (const TInstance& rhs){
	if (this == &rhs)
		return (*this);

	Texture::operator= (rhs);

	if (texture_ptr != NULL){
		delete texture_ptr;
		texture_ptr = NULL;
	}
	texture_ptr = rhs.texture_ptr;
	inv_matrix = rhs.inv_matrix;
	

	return (*this);
}

void
TInstance::scale(const double sx, const double sy, const double sz) {

	Matrix inv_scaling_matrix;			// temporary inverse scaling matrix

	inv_scaling_matrix.m[0][0] = 1.0 / sx;
	inv_scaling_matrix.m[1][1] = 1.0 / sy;
	inv_scaling_matrix.m[2][2] = 1.0 / sz;

	inv_matrix = inv_matrix * inv_scaling_matrix;
}

void TInstance::scale(const double s){
	scale(s, s, s);
}

void TInstance::translate(const double tx, const double ty, const double tz){
	Matrix inv_scaling_matrix;
	inv_scaling_matrix.m[0][3] = -tx;
	inv_scaling_matrix.m[1][3] = -ty;
	inv_scaling_matrix.m[2][3] = -tz;
	inv_matrix = inv_matrix * inv_scaling_matrix;
}

RGBColor
TInstance::get_color(const ShadeRec& sr) const {

	ShadeRec local_sr(sr);
	local_sr.local_hit_point = inv_matrix * local_sr.local_hit_point;

	return (texture_ptr->get_color(local_sr));
}