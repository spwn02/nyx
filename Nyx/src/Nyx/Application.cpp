#include "nyxpch.h"
#include "Application.h"

#include "Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Nyx {

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		NYX_CORE_ASSERT(!s_instance, "Application already exists!")
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(NYX_BIND_EVENT_FN(Application::onEvent));

		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer)
	{
		m_layerStack.pushOverlay(layer);
		layer->onAttach();
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(NYX_BIND_EVENT_FN(Application::onWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->onEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::run()
	{
		while (m_running)
		{
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_layerStack)
				layer->onUpdate();

			m_ImGuiLayer->begin();
			for (Layer* layer : m_layerStack)
				layer->onImGuiRender();
			m_ImGuiLayer->end();

			m_window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}
}