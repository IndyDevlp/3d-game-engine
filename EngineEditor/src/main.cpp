#include <iostream>
#include <memory>

#include "Core/Application.hpp"

class MyApp : public EngineCore::Application {

	virtual void on_update() override
	{
		//std::cout << "Update frame: " << frame++ << std::endl;
	}

	int frame = 0;
};

int main(int argc, char** argv)
{
	auto Engine_Window = std::make_unique<MyApp>();

	int returnCode = Engine_Window->start(1024, 768, "Keencloo Engine");

	std::cin.get();

	return returnCode;
}