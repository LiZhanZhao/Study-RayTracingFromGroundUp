#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Tracer.h"

class MultipleObjects: public Tracer {
	public:
		
		MultipleObjects(void);							
		
		MultipleObjects(World* _world_ptr);				
	
		virtual											
		~MultipleObjects(void);
						
		virtual RGBColor trace_ray(const Ray& ray) const;

		// ***** need to implement 
		// virtual RGBColor trace_ray(const Ray ray, const int depth) const;
};

#endif

