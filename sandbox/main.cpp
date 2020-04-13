#include <engine/application.h>

class Sandbox : public engine::Application {
public:
    Sandbox();
    ~Sandbox() override = default;

    void setup() override ;
    void shutdown() override ;
    void update() override ;

};

Sandbox::Sandbox() : engine::Application{} {
//    window = std::make_unique<engine::Window>();

}

void Sandbox::setup() {
    engine::Application::setup();
    logger->info("Hello from sandbox");
}

void Sandbox::shutdown() {
    engine::Application::shutdown();
    logger->info("Goodbye from sandbox");
}

void Sandbox::update() {
    get_window().update();
}


int main(int argc, char *argv[]) {
    Sandbox sandbox {};
    return sandbox.run();
}
