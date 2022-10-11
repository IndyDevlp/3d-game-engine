#include "Core/Application.hpp"
#include <Core/Log.hpp>

#include <GLFW/glfw3.h>

#include <iostream>

namespace EngineCore
{
	Application::Application()
	{
        LOG_INFO("Hello spd!");
        LOG_WARN("WARN");
        LOG_ERROR("ERROR");
        LOG_CRITICAL("fsdgdfgfd");
	}
	Application::~Application()
	{

	}
	int Application::start(unsigned window_width, unsigned window_height, const char* title)
	{
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return -1;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(window_width, window_height, title, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            //glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            on_update();
        }

        glfwTerminate();
        return 0;
	}
}

