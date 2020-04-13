#pragma once

#include <spdlog/logger.h>

#include "engine/window.h"
#include "engine/events/window.h"

namespace engine {
    class Application {
        using window_type = GLWindow;

    public:

        Application();
        virtual ~Application();

        virtual void create_window() {window = std::make_unique<window_type>(); }
        virtual window_type& get_window() {return *window;}

        static inline std::shared_ptr<spdlog::logger> logger;

        int run();
        virtual void setup();
        virtual void shutdown();
        virtual void update();

//        void on_window_event(const event::WindowEvent& event, Window &window);

        void stop() {
            running = false;
        }


    private:
        bool running {true};
        std::unique_ptr<window_type> window;
        static inline std::shared_ptr<spdlog::logger> _core_logger;

    };


}
