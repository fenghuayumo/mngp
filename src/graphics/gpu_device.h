#pragma once
#include "utility/Singleton.h"
#include <memory>
namespace NerfShot
{
    class GpuContext;
    class GpuDevice : public TSingleton<GpuDevice>
    {
    public:
        void initialize();
        void destroy();

        GpuContext* get_main_context() { return m_context.get();}    
    protected:
        class std::unique_ptr<GpuContext> m_context;
    };
}