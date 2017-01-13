#ifndef __FLAT_UV_MESH_TRIANGLE__
#define __FLAT_UV_MESH_TRIANGLE__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// FlatMeshTriangle is a MeshTriangle that uses flat shading with a constant normal
// This uses the inherited shadow hit function from MeshTriangle

#include "FlatMeshTriangle.h"

class FlatUVMeshTriangle : public FlatMeshTriangle {
	public:
		
		FlatUVMeshTriangle(void);
		
		FlatUVMeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);

		virtual FlatUVMeshTriangle*
		clone(void) const;
	
		FlatUVMeshTriangle(const FlatUVMeshTriangle& fmt);

		virtual
			~FlatUVMeshTriangle(void);

		FlatUVMeshTriangle&
			operator= (const FlatUVMeshTriangle& rhs);
				
		virtual	bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const; 																	
};

#endif

