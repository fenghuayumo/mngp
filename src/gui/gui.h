#pragma once
#include "Platform/window.h"

namespace NerfShot
{
    class EditGui
    {
    public:
        void init(Window* window);

		void render();

		void begin();

		void end();

		void shut_down();
    };
}
