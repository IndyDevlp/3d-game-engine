#pragma once

#include "Core/Event.hpp"
#include "Core/Camera.hpp"

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
		//bool set_image(const char** path_to_image);
		
		virtual int start(unsigned window_width, unsigned window_height, const char* title);
		virtual void on_update() {}

		virtual void on_ui_draw() {}

		virtual void on_mouse_button_event(const MouseButton button_code, const double x_pos, const double y_pos, const bool pressed) {}

		glm::vec2 get_current_cursor_position() const;

		float camera_pos[3] = { 0.f, 0.f, 1.f };
		float camera_rotation[3] = { 0.f, 0.f, 0.f };
		bool perspective_camera = true;
		Camera camera{ glm::vec3(-5,0,0) };

	private:

		std::unique_ptr<class Window> m_pWindow;
		

		EventDispatcher m_event_dispatcher;

		bool m_bCloseWindow = false;
	};
}