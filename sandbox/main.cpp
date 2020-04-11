#include <engine/application.h>
#include <engine/entrypoint.h>

#include <cstdio>

class Sandbox : public engine::Application {
public:
    Sandbox() = default;
    ~Sandbox() override = default;

    void run() override ;

};


void Sandbox::run() {
    printf("hello from sandbox!\n");
    engine::Application::run();
}

engine::Application* engine::create_application() {
    return new Sandbox();
}

