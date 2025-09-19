#pragma once

#include <memory>

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace Nyx {
  class Log
  {
  public:
    static NYX_API void init();

    inline static NYX_API std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; };
    inline static NYX_API std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; };
  private:
    static NYX_API std::shared_ptr<spdlog::logger> s_coreLogger;
    static NYX_API std::shared_ptr<spdlog::logger> s_clientLogger;
  };
}

// Core log macros
#define NYX_CORE_TRACE(...)   ::Nyx::Log::getCoreLogger()->trace(__VA_ARGS__)
#define NYX_CORE_INFO(...)    ::Nyx::Log::getCoreLogger()->info(__VA_ARGS__)
#define NYX_CORE_WARN(...)    ::Nyx::Log::getCoreLogger()->warn(__VA_ARGS__)
#define NYX_CORE_ERROR(...)   ::Nyx::Log::getCoreLogger()->error(__VA_ARGS__)
#define NYX_CORE_FATAL(...)   ::Nyx::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define NYX_TRACE(...)	      ::Nyx::Log::getClientLogger()->trace(__VA_ARGS__)
#define NYX_INFO(...)	      ::Nyx::Log::getClientLogger()->info(__VA_ARGS__)
#define NYX_WARN(...)	      ::Nyx::Log::getClientLogger()->warn(__VA_ARGS__)
#define NYX_ERROR(...)	      ::Nyx::Log::getClientLogger()->error(__VA_ARGS__)
#define NYX_FATAL(...)	      ::Nyx::Log::getClientLogger()->critical(__VA_ARGS__)
