#include<iostream>
#include"World.h"
int main()
{
	//std::cout << "hello ray tracing" << std::endl;

	World w;
	w.build();
	//w.render_scene();
	//w.render_perspective_scene();
	w.camera_ptr->render_scene(w);
	w.outputPPMImage("Image/test.ppm");

	std::cout << " *** Finish *** " << std::endl;

	return 0;
}