#pragma once

#include "Nyx/Window.h"

struct GLFWwindow;

namespace Nyx {
  class WindowsWindow : public Window
  {
  public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();

    void onUpdate() override;

    inline unsigned int getWidth() const override { return m_data.width; }
    inline unsigned int getHeight() const override { return m_data.height; }

    // Window attributes
    inline void setEventCallback(const EventCallbackFunction& callback) override { m_data.eventCallback = callback; }
    void setVSync(bool enabled) override;
    bool isVSync() const override;

    inline virtual void* getNativeWindow() const override { return m_window; };
  private:
    virtual void init(const WindowProps& props);
    virtual void shutdown();
  private:
    GLFWwindow* m_window;

    struct WindowData
    {
      std::string title;
      unsigned int width, height;
      bool VSync;
      
      EventCallbackFunction eventCallback;
    };

    WindowData m_data;
  };
}