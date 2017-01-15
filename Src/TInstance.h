#ifndef __TINSTANCE__
#define __TINSTANCE__

#include "Constants.h"
#include "Texture.h"

class TInstance : public Texture {
public:

	// constructors etc
	TInstance(void);

	TInstance(Texture* tex);

	TInstance(const TInstance& texture);

	virtual TInstance* clone(void) const;

	virtual ~TInstance(void);

	TInstance& operator= (const TInstance& rhs);

	void
		set_texture(Texture* t_ptr);

	virtual RGBColor
		get_color(const ShadeRec& sr) const;

	// affine tranformation functions:

	void scale(const double sx, const double sy, const double sz);

	void scale(const double s);

	void translate(const double tx, const double ty, const double tz);
	

private:

	Texture* 	texture_ptr;	// texture being transformed
	Matrix		inv_matrix;		// inverse transformation matrix
};


#endif