#include "nyxpch.h"
#include "Application.h"

#include "Nyx/Events/ApplicationEvent.h"
#include "Log.h"

namespace Nyx {
	Application::Application()
	{
	}
	Application::~Application()
	{
	}

	void Application::run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.isInCategory(EventCategoryApplication))
		{
			NYX_TRACE(e.toString());
			NYX_TRACE("App: YES");
		}
		if (e.isInCategory(EventCategoryInput))
		{
			NYX_TRACE(e.toString());
			NYX_TRACE("Input: NO");
		}

		while (true);
	}
}