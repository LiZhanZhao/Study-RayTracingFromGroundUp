#ifndef __SMOOTH_UV_MESH_TRIANGLE__
#define __SMOOTH_UV_MESH_TRIANGLE__


#include "SmoothMeshTriangle.h"

class SmoothUVMeshTriangle : public SmoothMeshTriangle
{
	public:
		SmoothUVMeshTriangle(void);

		SmoothUVMeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);

		virtual SmoothUVMeshTriangle*
			clone(void) const;

		SmoothUVMeshTriangle(const SmoothUVMeshTriangle& fmt);

		virtual
			~SmoothUVMeshTriangle(void);

		SmoothUVMeshTriangle&
			operator= (const SmoothUVMeshTriangle& rhs);

		virtual	bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
};

#endif