#include <Nyx.h>

class Sandbox : public Nyx::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Nyx::Application* Nyx::createApplication()
{
	return new Sandbox();
}