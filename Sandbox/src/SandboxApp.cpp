#include <Nyx.h>

class ExampleLayer : public Nyx::Layer
{
public:
  ExampleLayer()
    : Layer("Example")
  {
  }

  void onUpdate() override
  {
    if (Nyx::Input::isKeyPressed(NYX_KEY_TAB))
      NYX_TRACE("Tab key is pressed!");
  }

  void onEvent(Nyx::Event& event) override
  {
    if (event.getEventType() == Nyx::EventType::KeyPressed)
    {
      Nyx::KeyPressedEvent& e = (Nyx::KeyPressedEvent&)event;
      if (e.getKeyCode() == NYX_KEY_TAB)
        NYX_TRACE("Tab key is pressed!");
      NYX_TRACE("{0}", (char)e.getKeyCode());
    }
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