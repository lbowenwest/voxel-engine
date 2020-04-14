#include <engine/application.h>
#include <engine/window.h>
#include <engine/events/all.h>

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
    using engine::Window;
    using engine::event::WindowCloseEvent;
    using engine::event::MouseButtonPressedEvent;
    using engine::event::KeyPressedEvent;

    logger->info("Hello from sandbox");

    logger->info("Registering callbacks");
    get_window().once<WindowCloseEvent>(
            [=](const WindowCloseEvent &event, Window &window) {
                logger->info("Close event");
                stop();
            }
    );

    get_window().on<MouseButtonPressedEvent>(
            [=](const MouseButtonPressedEvent &event, Window &window) {
                logger->info("Mouse button {0} pressed", event.button);
            }
    );
    get_window().on<engine::event::KeyPressedEvent>(
            [=](const KeyPressedEvent &event, Window &window) {
                logger->info("Key pressed: {0}", event.keycode);
            }
    );
}

void Sandbox::shutdown() {
    logger->info("Goodbye from sandbox");
    get_window().clear();
}

void Sandbox::update() {
    get_window().update();
}


int main(int argc, char *argv[]) {
    Sandbox sandbox {};
    return sandbox.run(argc, argv);
}
