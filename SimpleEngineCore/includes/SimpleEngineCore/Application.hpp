#pragma once

#include <memory>

#include "SimpleEngineCore/Event.hpp"

namespace SimpleEngine {

    class Application
    {
    public:
        Application();
        virtual ~Application();

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        virtual int start(unsigned int window_width, unsigned int window_height, const char* title);

        virtual void on_update() {}

    private:
        EventDispatcher m_eventDispatcher;
        bool m_bCLoseWindow = false;

        std::unique_ptr<class Window> m_pWindow;

    };

}