#pragma once

#include <spdlog/spdlog.h>

#include "engine/application.h"

namespace engine {
    extern Application* create_application();

}

int main(int argc, char* argv[]) {
    spdlog::info("Starting from entry point");

    auto app = engine::create_application();
    app->run();
    delete app;

    return 0;
}