#pragma once

#ifdef NYX_PLATFORM_WINDOWS
  #if NYX_DLL
    #ifdef NYX_BUILD_DLL
      #define NYX_API __declspec(dllexport)
    #else
      #define NYX_API __declspec(dllimport)
    #endif
  #else
    #define NYX_API
  #endif
#else
  #error Nyx only supports Windows!
#endif

#ifdef NYX_DEBUG
  #define NYX_ENABLE_ASSERTS
#endif

#ifdef NYX_ENABLE_ASSERTS
  #define NYX_ASSERT(x, ...) { if(!(x)) { NYX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
  #define NYX_CORE_ASSERT(x, ...) { if(!(x)) { NYX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
  #define NYX_ASSERT(x, ...)
  #define NYX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define NYX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
