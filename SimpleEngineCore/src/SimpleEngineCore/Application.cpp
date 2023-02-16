#include <iostream>

#include "SimpleEngineCore/Application.hpp"
#include "SimpleEngineCore/Log.hpp"
#include "SimpleEngineCore/Window.hpp"

namespace SimpleEngine
{
    Application::Application()
    {
        LOG_INFO("Application::Application -> Starting Application");
    }
    Application::~Application()
    {
        LOG_INFO("Application::Application -> Closing Application");
    }
    int Application::start(unsigned int window_width, unsigned int window_height, const char* title)
    {
        m_pWindow = std::make_unique<Window>(title, window_width, window_height);

        m_eventDispatcher.add_event_listener<EventMouseMoved>
        (
            [](EventMouseMoved& event)
            {
                LOG_INFO("Application::start -> [Mouse Moved] to {0}x{1}", event.x, event.y);
            }
        );

        m_eventDispatcher.add_event_listener<EventWindowResize>
        (
            [](EventWindowResize& event)
            {
                LOG_INFO("Application::start -> [Resized] Change size to {0}x{1}", event.height, event.width);
            }
        );

        m_eventDispatcher.add_event_listener<EventWindowClose>
        (
            [&](EventWindowClose& event)
            {
                LOG_INFO("Application::start -> [Window Close]");
                m_bCLoseWindow = true;
            }
        );

        m_pWindow->set_event_callback(
            [&](BaseEvent& event)
            {
                m_eventDispatcher.dispatch(event);
            }
        );

        while (!m_bCLoseWindow)
        {
            m_pWindow->on_update();
            on_update();
        }
        m_pWindow = nullptr;
        return 0;
	}
}