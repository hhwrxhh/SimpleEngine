#include "SimpleEngineCore/Window.hpp"
#include "SimpleEngineCore/Log.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SimpleEngine
{
    static bool s_GLFW_initialize = false;

	Window::Window(std::string title, const unsigned int widht, const unsigned int height)
		: m_width(widht)
		, m_height(height)
		, m_title(std::move(title))
	{
		int resultCode = init();
	}
	Window::~Window()
	{
	}
	void Window::on_update()
	{
        glClearColor(0, 0, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
	}
	int Window::init()
	{
        LOG_INFO("Window::init -> Creating window `{0}` width size {1}x{2}", m_title, m_width, m_height);

        if (!s_GLFW_initialize)
        {
            if (!glfwInit())
            {
                LOG_CRITICAL("Window::init -> Can not initialize GLFW");
                return -1;
            }
            s_GLFW_initialize = true;
        }

        m_pWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
        if (!m_pWindow)
        {
            LOG_CRITICAL("Window::init -> Can not create Window {0}", m_title);
            glfwTerminate();
            return -2;
        }

        glfwMakeContextCurrent(m_pWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRITICAL("Window::init -> Failed to initialize GLAD");
            return -3;
        }

        return 0; 
	}
	void Window::shutdown()
	{
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
	}
}