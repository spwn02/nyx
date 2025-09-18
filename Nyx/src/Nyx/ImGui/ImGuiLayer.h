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
    
    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onImGuiRender() override;

    void begin();
    void end();
  private:
    float m_time = 0.0f;
  };
}