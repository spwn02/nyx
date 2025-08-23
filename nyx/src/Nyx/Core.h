#pragma once

#ifdef NYX_PLATFORM_WINDOWS
	#ifdef NYX_BUILD_DLL
		#define NYX_API __declspec(dllexport)
	#else
		#define NYX_API __declspec(dllimport)
	#endif
#else
	#error Nyx only supports Windows!
#endif
