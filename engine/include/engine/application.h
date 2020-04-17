#pragma once

#include <spdlog/logger.h>

#include "engine/window.h"
#include "engine/events/window.h"

namespace engine {
    class Application {

    public:

        Application();
        virtual ~Application();

        virtual std::unique_ptr<Window> create_window(Properties properties);
        Window& get_window();


        int run(int argc, char* argv[]);
        void stop();
        void initialise();
        void destroy();

        virtual void setup();
        virtual void shutdown();
        virtual void update();

        static inline std::shared_ptr<spdlog::logger> logger;

    protected:
        std::unique_ptr<Window> window;

    private:
        bool running {true};
        static inline std::shared_ptr<spdlog::logger> _core_logger;

    };


}
