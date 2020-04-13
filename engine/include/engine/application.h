#pragma once

#include <spdlog/logger.h>

#include "engine/window.h"
#include "engine/events/window.h"

namespace engine {
    class Application {

    public:

        Application();
        virtual ~Application();

        virtual std::unique_ptr<Window> create_window() {
            return std::make_unique<Window>(Properties{"window", {1280, 720}});
        }
        virtual Window& get_window() {
            return *window;
        }

        static inline std::shared_ptr<spdlog::logger> logger;

        int run();
        virtual void setup();
        virtual void shutdown();
        virtual void update();

        void stop() {
            running = false;
        }


    private:
        bool running {true};
        std::unique_ptr<Window> window;
        static inline std::shared_ptr<spdlog::logger> _core_logger;

    };


}
