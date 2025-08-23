#pragma once

#ifdef NYX_PLATFORM_WINDOWS

extern Nyx::Application* Nyx::createApplication();

int main(int argc, char** argv)
{
	auto app = Nyx::createApplication();
	app->run();
	delete app;
}

#endif