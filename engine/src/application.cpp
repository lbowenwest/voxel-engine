#include "engine/application.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace engine {

    Application::Application() {
        _core_logger = spdlog::stdout_color_mt("engine");
        logger = spdlog::stdout_color_mt("client");
    }

    Application::~Application() = default;

    void Application::run() {
        _core_logger->info("Starting application...");

    }

}