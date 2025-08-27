cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# Create project
project("Nyx" VERSION 1.0)

# Add library (Nyx Engine dll)
add_library(Nyx SHARED
	"Nyx/src/Nyx/Application.cpp"
	"Nyx/src/Nyx/Log.cpp"
)
set_target_properties(Nyx PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}
)
# Add executable
add_executable(Sandbox "Sandbox/src/SandboxApp.cpp")

# Link Nyx to Sandbox
target_link_libraries(Sandbox PUBLIC Nyx)

# Set Sandbox project as a startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

# Include necessary header files
include_directories(
	"Nyx/src"
	"Nyx/src/Nyx"
)

target_precompile_headers(Nyx PRIVATE Nyx/src/nyxpch.h)

# CPM
include(cmake/CPM.cmake)

CPMAddPackage("gh:gabime/spdlog@1.15.3")

target_link_libraries(Nyx spdlog::spdlog)

# Restrain this project to Windows-only
if(WIN32)
	# Set C++ standard to C++23
	set(CXX_STANDARD 23)
	set(CXX_STANDARD_REQUIRED TRUE)

	target_compile_definitions(Nyx
		PUBLIC NYX_PLATFORM_WINDOWS
		PRIVATE NYX_BUILD_DLL
	)
else()
	message(FATAL_ERROR "This project is only supported on Windows.")
endif()

# Define compile options and definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	# Turn on static runtime
	add_compile_options(/MTd -O0 -g /utf-8)
	target_compile_definitions(Nyx
		PUBLIC NYX_DEBUG
	)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	# Turn on static runtime
	add_compile_options(/MT)
	target_compile_definitions(Nyx
		PUBLIC NYX_RELEASE
	)
elseif(CMAKE_BUILD_TYPE STREQUAL "Dist")
	# Turn on static runtime
	add_compile_options(/MT)
	target_compile_definitions(Nyx
		PUBLIC NYX_DIST
	)
endif()
