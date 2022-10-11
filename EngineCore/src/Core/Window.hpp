#pragma once

#include <string>

struct GLFWwindow;

namespace EngineCore {

	class Window {
	public:
		Window(std::string title, const unsigned width, const unsigned height);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window operator=(const Window&) = delete;
		Window operator=(Window&&) = delete;
		
		void on_update();
		unsigned get_width() const { return m_width; }
		unsigned get_height() const { return m_height; }

	private:
		int init();
		void shutdown();

		GLFWwindow* m_pWindow;

		std::string m_title;

		unsigned m_width;
		unsigned m_height;
		
	};

}