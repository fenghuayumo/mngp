#include "gpu_context.h"
#  ifdef _WIN32
#    include <GL/gl3w.h>
#  else
#    include <GL/glew.h>
#  endif
#include "platform/window.h"

namespace NerfShot
{
    void GpuContext::begin_frame(Window* window)
    {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0., 0., 0., 0.);
		glViewport(0, 0, window->GetWidth(), window->GetHeight());
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GpuContext::end_frame(Window* window)
    {


    }
}
