#ifndef __FRESNEL_TRANSMITTER__
#define __FRESNEL_TRANSMITTER__

#include "BTDF.h"

class FresnelTransmitter : public BTDF {
public:

	FresnelTransmitter(void);

	FresnelTransmitter(const FresnelTransmitter& pt);

	virtual FresnelTransmitter*
		clone(void);

	~FresnelTransmitter(void);

	FresnelTransmitter&
		operator= (const FresnelTransmitter& rhs);

	void set_ior(const float eta);

	bool tir(const ShadeRec& sr) const;

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

	float fresnel(const ShadeRec& sr) const;

	void set_eta_in(float value);

	void set_eta_out(float value);

private:
	float	ior;		// index of refraction
	float eta_in;
	float eta_out;
};


inline void
FresnelTransmitter::set_ior(const float eta) {
	ior = eta;
}

inline void FresnelTransmitter::set_eta_in(float value){
	eta_in = value;
}

inline void FresnelTransmitter::set_eta_out(float value){
	eta_out = value;
}



#endif