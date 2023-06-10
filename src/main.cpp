#include "application.h"
#include "core/log.h"

class SceneViewer final : public NerfShot::Application
{
public:
	SceneViewer(const std::string& name = "SceneViewer")
		:NerfShot::Application(name)
	{
	}

	~SceneViewer()
	{
	}

	void OnImGuiRender()
	{

	}
private:
};

NerfShot::Application* NerfShot::CreateApplication(char** argv)
{
	return new SceneViewer();
}

int main(int argc, char** argv)
{
	NerfShot::Log::init();

	auto app = NerfShot::CreateApplication(argv);

	app->Run();

	app->Exit();
	delete app;
	NerfShot::Log::shut_down();
}
