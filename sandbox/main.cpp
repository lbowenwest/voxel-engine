#include <engine/application.h>
#include <engine/events/window.h>

class Sandbox : public engine::Application {
public:
    using window_type = engine::GLWindow;
    Sandbox();
    ~Sandbox() override = default;

//    void setup() override ;
//    void shutdown() override ;
//    void update() override ;

//    engine::Window* create_window() override;

//    void create_window() override {
//        window = std::make_unique<engine::GLWindow>();
//    }
//
//    engine::GLWindow& get_window() override {
//        return *window;
//    }

//    std::unique_ptr<engine::Window> window;

//private:
//    std::unique_ptr<engine::GLWindow> window;

};

Sandbox::Sandbox() : engine::Application{} {
//    window = std::make_unique<engine::Window>();

}
//
//void Sandbox::setup() {
//    logger->info("Hello from sandbox");
//
//    window->once<engine::event::WindowCloseEvent>(
//        [=](const engine::event::WindowCloseEvent& event, engine::Window& window) {
//            logger->info("Close event");
//            stop();
//        }
//    );
//
//    window->on<engine::event::MouseButtonPressedEvent>(
//        [=](const engine::event::MouseButtonPressedEvent &event, engine::Window &window) {
//            logger->info("Mouse button {0} pressed", event.button);
//        }
//    );
//    window->on<engine::event::KeyPressedEvent>(
//        [=](const engine::event::KeyPressedEvent &event, engine::Window &window) {
//            logger->info("Key pressed: {0}", event.keycode);
//        }
//    );
//}
//
//void Sandbox::shutdown() {
//    logger->info("Goodbye from sandbox");
//}
//
//void Sandbox::update() {
//    window->on_update();
//}

//engine::Window* create_window() {
//    engine::GLWindow window {};
//    window.init();
//
////    window.on<engine::event::WindowCloseEvent>([=](const engine::event::WindowCloseEvent& event, engine::GLWindow &window){});
//}

int main(int argc, char *argv[]) {
    Sandbox sandbox {};
    return sandbox.run();
}
