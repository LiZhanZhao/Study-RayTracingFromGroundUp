#include<iostream>
#include"Src\World.h"
int main()
{
	std::cout << "hello ray tracing" << std::endl;
	std::cout << "hello ray tracing" << std::endl;

	World w;
	w.build();
	w.render_scene();
	w.outputPPMImage("test.ppm");

	return 0;
}