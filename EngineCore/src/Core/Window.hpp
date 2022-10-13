#pragma once

#include "Core/Event.hpp"

#include <string>
#include <functional>

struct GLFWwindow;

namespace EngineCore {

	class Window {
	public:

		using EventCallbackFn = std::function<void(BaseEvent&)>;


		Window(std::string title, const unsigned width, const unsigned height);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window operator=(const Window&) = delete;
		Window operator=(Window&&) = delete;
		
		void on_update();
		unsigned get_width() const { return m_data.width; }
		unsigned get_height() const { return m_data.height; }

		void set_event_callback(const EventCallbackFn& callback)
		{
			m_data.eventCallbackFn = callback;
		}

	private:
		struct WindowData
		{
			std::string title;
			unsigned width;
			unsigned height;
			EventCallbackFn eventCallbackFn;
		};
		
		

		int init();
		void shutdown();

		GLFWwindow* m_pWindow = nullptr;	
		WindowData m_data;

		float m_background_color[4] = { 1.f, 1.f, 1.f, 0.f };



	};

}