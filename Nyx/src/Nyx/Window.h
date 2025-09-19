#pragma once

#include "nyxpch.h"

#include "Nyx/Core.h"
#include "Nyx/Events/Event.h"

namespace Nyx {
  struct WindowProps
  {
    std::string title;
    unsigned int width;
    unsigned int height;

    WindowProps(const std::string& title = "Nyx Engine",
                unsigned int width = 1280,
                unsigned int height = 720)
      : title(title), width(width), height(height) { };
  };

  // Interface representing a desktop system based Window
  class NYX_API Window
  {
  public:
    using EventCallbackFunction = std::function<void(Event&)>;

    virtual ~Window() {}

    virtual void onUpdate() = 0;

    virtual unsigned int getWidth() const = 0;
    virtual unsigned int getHeight() const = 0;

    // Window attributes
    virtual void setEventCallback(const EventCallbackFunction& callback) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual bool isVSync() const = 0;

    virtual void* getNativeWindow() const = 0;

    static Window* create(const WindowProps& props = WindowProps());
  };
}