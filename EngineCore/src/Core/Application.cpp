#include "Core/Application.hpp"
#include "Core/Log.hpp"
#include "Core/Window.hpp"

#include "Core/Rendering/OpenGL/ShaderProgram.hpp"
#include "Core/Rendering/OpenGL/VertexBuffer.hpp"
#include "Core/Rendering/OpenGL/VertexArray.hpp"
#include "Core/Rendering/OpenGL/IndexBuffer.hpp"
#include "Core/Camera.hpp"
#include "Core/Rendering/OpenGL/Renderer_OpenGL.hpp"
#include "Core/Modules/UIModule.hpp"
#include "Core/Input.hpp"

#include <imgui/imgui.h>
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>
#include <glm/mat3x3.hpp>
#include <iostream>

namespace EngineCore
{

	GLfloat positions_colors[] = {
		0.0f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
		0.0f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
		0.0f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
		0.0f,  0.5f,  0.5f,    1.0f, 0.0f, 1.0f,
	};

	GLuint indices[] = {
		0, 1, 2, 3, 2, 1
	};

	const char* vertex_shader =
		R"(#version 460
           layout(location = 0) in vec3 vertex_position;
           layout(location = 1) in vec3 vertex_color;
           uniform mat4 model_matrix;
           uniform mat4 view_projection_matrix;
           out vec3 color;
           void main() {
              color = vertex_color;
              gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
           }
        )";

	const char* fragment_shader =
		R"(#version 460
           in vec3 color;
           out vec4 frag_color;
           void main() {
              frag_color = vec4(color, 1.0);
           }
        )";

	GLuint shader_program;
	GLuint vao;

	std::unique_ptr<ShaderProgram> g_pShader_program;
	std::unique_ptr<IndexBuffer> g_pIndex_buffer;

	std::unique_ptr<VertexBuffer> g_pPositions_colors_vbo;
	std::unique_ptr<VertexArray> g_pVAO;

	float scale[3] = { 1.f,1.f,1.f };
	float rotate = 0.f;
	float translate[3] = { 0.f, 0.f, 0.f };

	float m_background_color[4] = { .5f, .5f, .5f, 0.f };

	Application::Application()
	{
		LOG_INFO("Starting Application");
	}
	Application::~Application()
	{
		LOG_INFO("Closing Application");
	}

	int Application::start(unsigned window_width, unsigned window_height, const char* title)
	{
		m_pWindow = std::make_unique<Window>(title, window_width, window_height);

		m_event_dispatcher.add_event_listener<EventMouseMoved>(
			[](EventMouseMoved& event)
			{
				//LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
			});

		m_event_dispatcher.add_event_listener<EventWindowResize>(
			[](EventWindowResize& event)
			{
				//LOG_INFO("[Resized] Changed size to {0}x{1}", event.width, event.height);
			});
		
		m_event_dispatcher.add_event_listener<EventWindowClose>(
			[&](EventWindowClose& event)
			{
				LOG_INFO("[WindowClose] Closed!");
				m_bCloseWindow = true;
			}
		);

		m_event_dispatcher.add_event_listener<EventMouseButtonPressed>(
			[&](EventMouseButtonPressed& event)
			{
				//LOG_INFO("[Mouse Button Pressed] - {0}, at ({1} {2})", event.mouse_button, event.x_pos, event.y_pos);

				Input::PressMouseButton(event.mouse_button);
				on_mouse_button_event(event.mouse_button, event.x_pos, event.y_pos, true);
			}
		);

		m_event_dispatcher.add_event_listener<EventMouseButtonReleased>(
			[&](EventMouseButtonReleased& event)
			{
				//LOG_INFO("[Mouse Button Released] - {0}, at ({1} {2})", event.mouse_button, event.x_pos, event.y_pos);

				Input::ReleaseMouseButton(event.mouse_button);
				on_mouse_button_event(event.mouse_button, event.x_pos, event.y_pos, false);
			}
		);

		m_event_dispatcher.add_event_listener<EventKeyPressed>(
			[&](EventKeyPressed& event)
			{
				if (event.key_code <= KeyCode::KEY_Z)
				{
					if (event.repeated)
					{
						LOG_INFO("[KeyPressed] KEY - {0}, repeated", static_cast<char>(event.key_code));
					}
					else
					{
						LOG_INFO("[KeyPressed] KEY - {0}", static_cast<char>(event.key_code));
					}
				}

				Input::Presskey(event.key_code);
			}
		);

		m_event_dispatcher.add_event_listener<EventKeyReleased>(
			[&](EventKeyReleased& event)
			{
				if (event.key_code <= KeyCode::KEY_Z)
				{
					LOG_INFO("[KeyReleased] KEY - {0}", static_cast<char>(event.key_code));
				}

				Input::ReleaseKey(event.key_code);
			}
		);
			
		m_pWindow->set_event_callback(
			[&](BaseEvent& event) {
				m_event_dispatcher.dispath(event);
			});


		//***********************************************
		g_pShader_program = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);
		if (!g_pShader_program->isCompiled()) return -1;

		BufferLayout buffer_layout_2vec3
		{
			ShaderDataType::Float3,
			ShaderDataType::Float3
		};

		g_pVAO = std::make_unique<VertexArray>();
		g_pPositions_colors_vbo = std::make_unique<VertexBuffer>(positions_colors, sizeof(positions_colors), buffer_layout_2vec3);
		g_pIndex_buffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

		g_pVAO->add_vertex_buffer(*g_pPositions_colors_vbo);
		g_pVAO->set_index_buffer(*g_pIndex_buffer);
		//***********************************************

		while (!m_bCloseWindow)
		{
			Renderer_OpenGL::set_clear_color(m_background_color[0], m_background_color[1], m_background_color[2], m_background_color[3]);
			Renderer_OpenGL::clear();

			


			g_pShader_program->bind();

			glm::mat4 scale_mat(scale[0], 0, 0, 0,
				0, scale[1], 0, 0,
				0, 0, scale[2], 0,
				0, 0, 0, 1);

			float rotate_in_rad = glm::radians(rotate);
			glm::mat4 rotate_matrix(cos(rotate_in_rad), sin(rotate_in_rad), 0, 0,
				-sin(rotate_in_rad), cos(rotate_in_rad), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

			glm::mat4 translate_matrix(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				translate[0], translate[1], translate[2], 1);

			glm::mat4 model_matrix = scale_mat * rotate_matrix * translate_matrix;

			g_pShader_program->setMatrix4("model_matrix", model_matrix);

			camera.set_projection_mode(perspective_camera ? Camera::ProjectionMode::Perspective : Camera::ProjectionMode::Orthographic);

			g_pShader_program->setMatrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());

			Renderer_OpenGL::draw(*g_pVAO);

			//***********************************************
			UIModule::on_ui_draw_begin();
			bool show = true;
			UIModule::ShowExampleAppDockSpace(&show);
			//ImGui::Begin("Background Color Window");
			//ImGui::ColorEdit4("Background Color", m_background_color);
			//ImGui::SliderFloat3("scale", scale, 0.f, 2.f);
			//ImGui::SliderFloat("rotate", &rotate, 0.f, 360.f);
			//ImGui::SliderFloat3("translate", translate, -1.f, 1.f);
			//ImGui::SliderFloat3("Camera position", camera_pos, -10.f, 10.f);
			//ImGui::SliderFloat3("Camera rotation", camera_rotation, 0.f, 360.f);
			//ImGui::Checkbox("Perspective camera", &perspective_camera);
			//ImGui::End();
			//***********************************************

			on_ui_draw();
			UIModule::on_ui_draw_end();
			

			m_pWindow->on_update();
			on_update();
		}

		m_pWindow = nullptr;

        return 0;
	}

	glm::vec2 Application::get_current_cursor_position() const
	{
		return m_pWindow->get_current_cursor_position();
	}
}

