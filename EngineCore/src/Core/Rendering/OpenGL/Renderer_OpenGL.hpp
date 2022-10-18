#pragma once

struct GLFWwindow;

namespace EngineCore {
	class VertexArray;

	class Renderer_OpenGL {
	public:
		static bool init(GLFWwindow* pWindow);

		static void draw(const VertexArray& vertex_array);
		static void set_clear_color(const float r, const float g, const float b, const float a);
		static void clear();
		static void set_viewport(const unsigned width, const unsigned height, const unsigned left_offset = 0, const unsigned bottom_offset = 0);

		static const char* get_vendor_str();
		static const char* get_renderer_str();
		static const char* get_version_str();

	};
}