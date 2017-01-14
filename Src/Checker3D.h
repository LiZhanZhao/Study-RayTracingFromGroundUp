#ifndef __CHECKER_3D__
#define __CHECKER_3D__

#include "Texture.h"

class Checker3D : public Texture
{
public:
	Checker3D(void);

	Checker3D(const Checker3D& texture);

	virtual Checker3D*
		clone(void) const;

	virtual
		~Checker3D(void);

	virtual RGBColor
		get_color(const ShadeRec& sr) const;

	void set_size(const float value);

	void set_color1(RGBColor color);
	void set_color2(RGBColor color);

protected:
	Checker3D& operator= (const Checker3D& rhs);
	float size;
	RGBColor color1, color2;
};

inline void Checker3D::set_size(const float value){

}

inline void Checker3D::set_color1(RGBColor color){
	color1 = color;
}

inline void Checker3D::set_color2(RGBColor color){
	color2 = color;
}

#endif