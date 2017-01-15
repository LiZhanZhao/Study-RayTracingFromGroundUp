#ifndef __PLANE_CHECKER__
#define __PLANE_CHECKER__

#include "Texture.h"

class PlaneChecker : public Texture{
public:
	PlaneChecker(void);

	PlaneChecker(const PlaneChecker& texture);

	virtual PlaneChecker* clone(void) const;

	virtual ~PlaneChecker(void);

	PlaneChecker& operator= (const PlaneChecker& rhs);

	virtual RGBColor
		get_color(const ShadeRec& sr) const;

	void set_size(const float value);

	void set_outline_width(const float value);

	void set_color1(RGBColor color);

	void set_color2(RGBColor color);

	void set_outline_color(RGBColor color);

protected:
	float size;
	float outline_width;
	RGBColor color1, color2, outline_color;

	

};

inline void PlaneChecker::set_size(const float value){
	size = value;
}

inline void PlaneChecker::set_outline_width(const float value){
	outline_width = value;
}

inline void PlaneChecker::set_color1(RGBColor color){
	color1 = color;
}

inline void PlaneChecker::set_color2(RGBColor color){
	color2 = color;
}

inline void PlaneChecker::set_outline_color(RGBColor color){
	outline_color = color;
}


#endif