#pragma once

#include "engine/application.h"

namespace engine {
    extern Application* create_application();

}

int main(int argc, char* argv[]) {
    auto app = engine::create_application();
    app->run();
    delete app;

    return 0;
}