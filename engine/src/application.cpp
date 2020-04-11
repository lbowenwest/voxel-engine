
#include "engine/application.h"

#include <spdlog/spdlog.h>

namespace engine {

    Application::Application() = default;

    Application::~Application() = default;

    void Application::run() {
        spdlog::info("Starting application...");

    }

}