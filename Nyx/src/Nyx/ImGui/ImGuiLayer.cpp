#include "nyxpch.h"
#include "ImGuiLayer.h"

#include <imgui.h>
#include "platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "platform/OpenGL/ImGuiGLFW.h"

#include "Application.h"

// Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Nyx {
  ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
  {

  }

  ImGuiLayer::~ImGuiLayer()
  {

  }

  void ImGuiLayer::onAttach()
  {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui_ImplOpenGL3_Init("#version 440");

    // ImGui_ImplGlfw_UpdateKeyModifiers(io, glfwGetCurrentContext());
  }

  void ImGuiLayer::onDetach()
  {

  }

  void ImGuiLayer::onUpdate()
  {
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::get();
    io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

    float time = (float)glfwGetTime();
    io.DeltaTime = m_time > 0.0 ? (time - m_time) : (1.0f / 60.0f);
    m_time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void ImGuiLayer::onEvent(Event& event)
  {
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<MouseButtonPressedEvent>(NYX_BIND_EVENT_FN(ImGuiLayer::onMouseButtonPressedEvent));
    dispatcher.dispatch<MouseButtonReleasedEvent>(NYX_BIND_EVENT_FN(ImGuiLayer::onMouseButtonReleasedEvent));
    dispatcher.dispatch<MouseMovedEvent>(NYX_BIND_EVENT_FN(ImGuiLayer::onMouseMovedEvent));
    dispatcher.dispatch<MouseScrolledEvent>(NYX_BIND_EVENT_FN(ImGuiLayer::onMouseScrolledEvent));
    dispatcher.dispatch<KeyPressedEvent>(NYX_BIND_EVENT_FN(ImGuiLayer::onKeyPressedEvent));
    dispatcher.dispatch<KeyTypedEvent>(NYX_BIND_EVENT_FN(ImGuiLayer::onKeyTypedEvent));
    dispatcher.dispatch<KeyReleasedEvent>(NYX_BIND_EVENT_FN(ImGuiLayer::onKeyReleasedEvent));
    dispatcher.dispatch<WindowResizeEvent>(NYX_BIND_EVENT_FN(ImGuiLayer::onWindowResizedEvent));
  }

  bool ImGuiLayer::onMouseButtonPressedEvent(MouseButtonPressedEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(e.getMouseButton(), true);

    return false;
  }
  
  bool ImGuiLayer::onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(e.getMouseButton(), false);

    return false;
  }

  bool ImGuiLayer::onMouseMovedEvent(MouseMovedEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMousePosEvent(e.getX(), e.getY());

    return false;
  }

  bool ImGuiLayer::onMouseScrolledEvent(MouseScrolledEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseWheelEvent(e.getXOffset(), e.getYOffset());

    return false;
  }

  bool ImGuiLayer::onKeyPressedEvent(KeyPressedEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    ImGuiKey key = ImGui_ImplGlfw_KeyToImGuiKey(e.getKeyCode(), glfwGetKeyScancode(e.getKeyCode()));

    io.AddKeyEvent(key, true);
    
    return false;
  }

  bool ImGuiLayer::onKeyReleasedEvent(KeyReleasedEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    ImGuiKey key = ImGui_ImplGlfw_KeyToImGuiKey(e.getKeyCode(), glfwGetKeyScancode(e.getKeyCode()));

    io.AddKeyEvent(key, false);
    NYX_CORE_TRACE(e.toString());

    return false;
  }

  bool ImGuiLayer::onKeyTypedEvent(KeyTypedEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    int keycode = e.getKeyCode();
    if (keycode > 0 && keycode < 0x10000)
      io.AddInputCharacter((unsigned short)keycode);

    return false;
  }

  bool ImGuiLayer::onWindowResizedEvent(WindowResizeEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(e.getWidth(), e.getHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    glViewport(0, 0, e.getWidth(), e.getHeight());

    return false;
  }
}
