#include <engine/application.h>
#include <engine/entrypoint.h>

class Sandbox : public engine::Application {
public:
    Sandbox() = default;
    ~Sandbox() override = default;

    void run() override ;

};


void Sandbox::run() {
    logger->info("Hello from sandbox");
    engine::Application::run();
}

engine::Application* engine::create_application() {
    return new Sandbox();
}

