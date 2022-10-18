#include <iostream>
#include <memory>
#include <imgui/imgui.h>
#include "Core/Application.hpp"

class KeenclooEngineEditor : public EngineCore::Application {

	virtual void on_update() override
	{
		//std::cout << "Update frame: " << frame++ << std::endl;
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