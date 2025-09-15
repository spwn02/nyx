#include "nyxpch.h"
#include "WindowsWindow.h"

#include "Nyx/Events/ApplicationEvent.h"
#include "Nyx/Events/MouseEvent.h"
#include "Nyx/Events/KeyEvent.h"

#include <glad/glad.h>
#include <imgui.h>

namespace Nyx {
  static bool s_GLFWInitialized = false;

  static void GLFWErrorCallback(int error, const char* description)
  {
    NYX_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
  }

  Window* Window::create(const WindowProps& props)
  {
    return new WindowsWindow(props);
  }

  WindowsWindow::WindowsWindow(const WindowProps& props)
  {
    init(props);
  }

  WindowsWindow::~WindowsWindow()
  {
    shutdown();
  }

  void WindowsWindow::init(const WindowProps& props)
  {
    m_data.title = props.title;
    m_data.width = props.width;
    m_data.height = props.height;

    NYX_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);
    
    if (!s_GLFWInitialized)
    {
      // TODO: glfwTerminate on system shutdown
      int success = glfwInit();
      NYX_CORE_ASSERT(success, "Could not initialize GLFW!");

      glfwSetErrorCallback(GLFWErrorCallback);

      s_GLFWInitialized = true;
    }

    m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    NYX_CORE_ASSERT(status, "Failed to initialize Glad!")
    glfwSetWindowUserPointer(m_window, &m_data);
    setVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      data.width = width;
      data.height = height;

      WindowResizeEvent event(width, height);
      data.eventCallback(event);
    });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      WindowCloseEvent event;
      data.eventCallback(event);
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

      switch (action)
      {
        case GLFW_PRESS:
        {
          KeyPressedEvent event(key, 0);
          data.eventCallback(event);
          break;
        }
        case GLFW_RELEASE:
        {
          KeyReleasedEvent event(key);
          data.eventCallback(event);
          break;
        }
        case GLFW_REPEAT:
        {
          KeyPressedEvent event(key, 1);
          data.eventCallback(event);
          break;
        }
      }
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

      switch (action)
      {
        case GLFW_PRESS:
        {
          MouseButtonPressedEvent event(button);
          data.eventCallback(event);
          break;
        }
        case GLFW_RELEASE:
        {
          MouseButtonReleasedEvent event(button);
          data.eventCallback(event);
          break;
        }
      }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

      MouseScrolledEvent event((float)xOffset, (float)yOffset);
      data.eventCallback(event);
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

      MouseMovedEvent event((float)xPos, (float)yPos);
      data.eventCallback(event);
    });
  }

  void WindowsWindow::shutdown()
  {
    glfwDestroyWindow(m_window);
  }

  void WindowsWindow::onUpdate()
  {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
  }

  void WindowsWindow::setVSync(bool enabled)
  {
    if (enabled)
      glfwSwapInterval(1);
    else
      glfwSwapInterval(0);

    m_data.VSync = enabled;
  }

  bool WindowsWindow::isVSync() const
  {
    return m_data.VSync;
  }
}