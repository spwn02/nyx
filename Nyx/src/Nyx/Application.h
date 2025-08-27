#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Nyx {
	class NYX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// To be defined in Client
	Application* createApplication();
}
