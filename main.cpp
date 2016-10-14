#include<iostream>
#include"Src\World.h"
int main()
{
	//std::cout << "hello ray tracing" << std::endl;

	World w;
	w.build();
	//w.render_scene();
	w.render_perspective_scene();
	w.outputPPMImage("Image/test.ppm");

	std::cout << " *** Finish *** " << std::endl;

	return 0;
}