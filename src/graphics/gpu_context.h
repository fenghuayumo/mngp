#pragma once

namespace NerfShot
{
    class Window;
    class GpuContext
    {
    public:
        void begin_frame(Window* window);

        void end_frame(Window* window);
    };
}