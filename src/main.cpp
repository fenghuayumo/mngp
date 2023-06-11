#include "application.h"
#include "scene_viewer.h"


int main(int argc, char** argv)
{
	NerfShot::Log::init();

	auto app = NerfShot::CreateApplication(argv);

	app->Run();

	app->Exit();
	delete app;
	NerfShot::Log::shut_down();
}
