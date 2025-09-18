cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)

# Create project
project("Nyx" VERSION 1.0)

file(GLOB_RECURSE SRCS  "Nyx/src/*.cpp")
file(GLOB_RECURSE HDRS  "Nyx/src/*.h")
file(GLOB_RECURSE PSRCS "Nyx/platform/*.cpp")
file(GLOB_RECURSE PHDRS "Nyx/platform/*.h")

# Add library (Nyx Engine dll)
add_library(Nyx SHARED
	${SRCS} ${HDRS}
	${PSRCS} ${PHDRS}
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
target_include_directories(Nyx PUBLIC
	"Nyx/src"
)

target_include_directories(Nyx PRIVATE
	"Nyx/dependencies"
	"Nyx/src/Nyx"
	"Nyx"
)

# Precompile headers
target_precompile_headers(Nyx PRIVATE Nyx/src/nyxpch.h)

# Libraries
include(cmake/CPM.cmake)

find_package(OpenGL REQUIRED)
CPMAddPackage("gh:gabime/spdlog#v1.15.3")
CPMAddPackage("gh:glfw/glfw#3.4")
CPMAddPackage("gh:ocornut/imgui#v1.92.0")

set(DEPS "Nyx/dependencies")

#! Glad
add_library(glad "${DEPS}/glad/src/glad.c")
target_include_directories(glad PUBLIC "${DEPS}/glad/include")

#! ImGui
add_library(imgui
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
)
target_include_directories(imgui SYSTEM PUBLIC
	${imgui_SOURCE_DIR}
)

target_link_libraries(Nyx PUBLIC
	OpenGL::GL
	opengl32.lib
	glfw
	spdlog::spdlog
	glad
	imgui
)

# Restrain this project to Windows-only
if(WIN32)
	# Set C++ standard to C++23
	set(CXX_STANDARD 23)
	set(CXX_STANDARD_REQUIRED TRUE)

	target_compile_definitions(Nyx
		PUBLIC NYX_PLATFORM_WINDOWS
		PRIVATE NYX_BUILD_DLL
		PRIVATE GLFW_INCLUDE_NONE
	)
else()
	message(FATAL_ERROR "This project is only supported on Windows.")
endif()

# Define compile options and definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	# Turn on static runtime
	add_compile_options(/MDd -O0 -g /utf-8)
	target_compile_definitions(Nyx
		PRIVATE NYX_DEBUG
	)
	set_property(TARGET Nyx PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	set_property(TARGET Sandbox PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	# Turn on static runtime
	add_compile_options(/MD)
	target_compile_definitions(Nyx
		PRIVATE NYX_RELEASE
	)
elseif(CMAKE_BUILD_TYPE STREQUAL "Dist")
	# Turn on static runtime
	add_compile_options(/MD)
	target_compile_definitions(Nyx
		PRIVATE NYX_DIST
	)
endif()
