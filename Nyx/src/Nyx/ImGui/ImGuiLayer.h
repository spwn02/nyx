#pragma once

#include "Nyx/Layer.h"

#include "Nyx/Events/ApplicationEvent.h"
#include "Nyx/Events/KeyEvent.h"
#include "Nyx/Events/MouseEvent.h"

namespace Nyx {
  class NYX_API ImGuiLayer : public Layer
  {
  public:
    ImGuiLayer();
    ~ImGuiLayer();
    
    void onAttach();
    void onDetach();
    void onUpdate();
    void onEvent(Event& event);
  private:
    bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
    bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
    bool onMouseMovedEvent(MouseMovedEvent& e);
    bool onMouseScrolledEvent(MouseScrolledEvent& e);
    bool onKeyPressedEvent(KeyPressedEvent& e);
    bool onKeyReleasedEvent(KeyReleasedEvent& e);
    bool onKeyTypedEvent(KeyTypedEvent& e);
    bool onWindowResizedEvent(WindowResizeEvent& e);
  private:
    float m_time = 0.0f;
  };
}