#pragma once
#include<memory>
// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
//#define SPDLOG_FMT_EXTERNAL 
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)


namespace NerfShot
{

	class Log
	{
	public:
		static void init();
		static void shut_down();
		static std::shared_ptr<spdlog::logger>& get_core_logger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& get_client_logger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define NRS_CORE_TRACE(...)    ::NerfShot::Log::get_core_logger()->trace(__VA_ARGS__)
#define NRS_CORE_INFO(...)     ::NerfShot::Log::get_core_logger()->info(__VA_ARGS__)
#define NRS_CORE_WARN(...)     ::NerfShot::Log::get_core_logger()->warn(__VA_ARGS__)
#define NRS_CORE_ERROR(...)    ::NerfShot::Log::get_core_logger()->error(__VA_ARGS__)
#define NRS_CORE_CRITICAL(...) ::NerfShot::Log::get_core_logger()->critical(__VA_ARGS__)

// Client log macros
#define NRS_TRACE(...)         ::NerfShot::Log::get_client_logger()->trace(__VA_ARGS__)
#define NRS_INFO(...)          ::NerfShot::Log::get_client_logger()->info(__VA_ARGS__)
#define NRS_WARN(...)          ::NerfShot::Log::get_client_logger()->warn(__VA_ARGS__)
#define NRS_ERROR(...)         ::NerfShot::Log::get_client_logger()->error(__VA_ARGS__)
#define NRS_CRITICAL(...)      ::NerfShot::Log::get_client_logger()->critical(__VA_ARGS__)
