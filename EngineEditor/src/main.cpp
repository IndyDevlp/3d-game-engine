#include <iostream>
#include <memory>
#include <imgui/imgui.h>
#include "Core/Application.hpp"
#include "Core/Input.hpp"

class KeenclooEngineEditor : public EngineCore::Application {

	virtual void on_update() override
	{
		if (EngineCore::Input::IsKeyPressed(EngineCore::KeyCode::KEY_W))
		{
			camera_pos[2] -= 0.01f;
		}
		if (EngineCore::Input::IsKeyPressed(EngineCore::KeyCode::KEY_S))
		{
			camera_pos[2] += 0.01f;
		}
		if (EngineCore::Input::IsKeyPressed(EngineCore::KeyCode::KEY_A))
		{
			camera_pos[0] -= 0.01f;
		}
		if (EngineCore::Input::IsKeyPressed(EngineCore::KeyCode::KEY_D))
		{
			camera_pos[0] += 0.01f;
		}
		if (EngineCore::Input::IsKeyPressed(EngineCore::KeyCode::KEY_E))
		{
			camera_pos[1] += 0.01f;
		}
		if (EngineCore::Input::IsKeyPressed(EngineCore::KeyCode::KEY_Q))
		{
			camera_pos[1] -= 0.01f;
		}
		if (EngineCore::Input::IsKeyPressed(EngineCore::KeyCode::KEY_UP))
		{
			camera_rotation[0] += 0.5f;
		}
		if (EngineCore::Input::IsKeyPressed(EngineCore::KeyCode::KEY_DOWN))
		{
			camera_rotation[0] -= 0.5f;
		}
		if (EngineCore::Input::IsKeyPressed(EngineCore::KeyCode::KEY_RIGHT))
		{
			camera_rotation[1] -= 0.5f;
		}
		if (EngineCore::Input::IsKeyPressed(EngineCore::KeyCode::KEY_LEFT))
		{
			camera_rotation[1] += 0.5f;
		}

	}

	virtual void on_ui_draw() override
	{
		ImGui::Begin("Editor");
		ImGui::SliderFloat3("Camera position", camera_pos, -10.f, 10.f);
		ImGui::SliderFloat3("Camera rotation", camera_rotation, 0.f, 360.f);
		ImGui::Checkbox("Perspective camera", &perspective_camera);
		ImGui::End();
	}

	int frame = 0;
};

int main(int argc, char** argv)
{
	auto pKeenclooEngineEditor = std::make_unique<KeenclooEngineEditor>();

	int returnCode = pKeenclooEngineEditor->start(1024, 768, "Keencloo [Editor]");

	std::cin.get();

	return returnCode;
}