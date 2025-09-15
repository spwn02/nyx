#include <Nyx.h>

class ExampleLayer : public Nyx::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{ }

	void onUpdate() override
	{
		// NYX_INFO("ExampleLayer::Update");
	}

	void onEvent(Nyx::Event& event) override
	{
		// NYX_INFO("{0}", event.toString());
	}
};

class Sandbox : public Nyx::Application
{
public:
	Sandbox()
	{
		pushLayer(new ExampleLayer());
	}
	
	~Sandbox()
	{

	}
};

Nyx::Application* Nyx::createApplication()
{
	return new Sandbox();
}