#pragma once

#include "Core/Event.hpp"

#include <memory>

namespace EngineCore {

	class Application {

	public:
		Application();
		virtual ~Application();

		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application operator=(const Application&) = delete;
		Application operator=(Application&&) = delete;
		bool set_image(const char** path_to_image);
		
		virtual int start(unsigned window_width, unsigned window_height, const char* title);
		virtual void on_update(){}

	private:

		std::unique_ptr<class Window> m_pWindow;
		

		EventDispatcher m_event_dispatcher;

		bool m_bCloseWindow = false;
	};
}