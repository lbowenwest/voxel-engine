#pragma once

#include <spdlog/logger.h>

namespace engine {
    class Application {

    public:
        Application();
        virtual ~Application();

        virtual void run();

        static inline std::shared_ptr<spdlog::logger> logger;

    private:
        static inline std::shared_ptr<spdlog::logger> _core_logger;
    };




}
