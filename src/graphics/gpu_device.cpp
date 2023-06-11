#include "gpu_device.h"
#  ifdef _WIN32
#    include <GL/gl3w.h>
#  else
#    include <GL/glew.h>
#  endif
namespace NerfShot
{
    void GpuDevice::initialize()
    {
#ifdef _WIN32
	if (gl3wInit()) {
		throw std::runtime_error{"GL3W could not be initialized."};
	}
#else
	glewExperimental = 1;
	if (glewInit()) {
		throw std::runtime_error{"GLEW could not be initialized."};
	}
#endif
    }

    void GpuDevice::destroy()
    {

    }
}