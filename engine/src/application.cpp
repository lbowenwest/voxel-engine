#include "engine/application.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace engine {

    Application::Application() {
        _core_logger = spdlog::stdout_color_mt("engine");
        logger = spdlog::stdout_color_mt("client");
    }

    Application::~Application() = default;

    std::unique_ptr<Window> Application::create_window(Properties properties) {
        return std::make_unique<Window>(std::move(properties));
    }

    Window& Application::get_window() {
        return *window;
    }

    void Application::initialise() {
        _core_logger->info("Initialising application...");

        window = create_window({"Window", {1280, 720}});

        window->once<event::WindowCloseEvent>(
                [=](const event::WindowCloseEvent &event, Window &window) {
                    logger->info("Close event");
                    stop();
                }
        );

        window->on<event::MouseButtonPressedEvent>(
                [=](const event::MouseButtonPressedEvent &event, Window &window) {
                    logger->info("Mouse button {0} pressed", event.button);
                }
        );
        window->on<engine::event::KeyPressedEvent>(
                [=](const event::KeyPressedEvent &event, Window &window) {
                    logger->info("Key pressed: {0}", event.keycode);
                }
        );

        setup();
    }

    void Application::destroy() {
        _core_logger->info("Destroying application...");
        shutdown();
    }

    int Application::run(int argc, char* argv[]) {
        initialise();

        while (running) {
            // do stuff
            update();
        }

        destroy();

        return 0;
    }

    void Application::stop() {
        _core_logger->info("Stop function called");
        running = false;
    }

    void Application::setup() {
        logger->info("Calling setup");
    }

    void Application::shutdown() {
        logger->info("Calling shutdown");
    }

    void Application::update() {
        get_window().update();
    }
}