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

int main(void)
{
	auto test_app = std::make_unique<MyApp>();

	int returnCode = test_app->start(1024, 768, "Guncle Engine");

	std::cin.get();

	return returnCode;
}