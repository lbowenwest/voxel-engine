#include "engine/application.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace engine {

    Application::Application() {

        _core_logger = spdlog::stdout_color_mt("engine");
        logger = spdlog::stdout_color_mt("client");

    }

    Application::~Application() = default;

    void Application::setup() {
        logger->info("Performing application setup");

        window = create_window();

        get_window().once<event::WindowCloseEvent>(
                [=](const event::WindowCloseEvent &event, Window &window) {
                    logger->info("Close event");
                    stop();
                }
        );

        get_window().on<event::MouseButtonPressedEvent>(
                [=](const event::MouseButtonPressedEvent &event, Window &window) {
                    logger->info("Mouse button {0} pressed", event.button);
                }
        );
        get_window().on<engine::event::KeyPressedEvent>(
                [=](const event::KeyPressedEvent &event, Window &window) {
                    logger->info("Key pressed: {0}", event.keycode);
                }
        );
    }

    void Application::shutdown() {
        logger->info("Performing application shutdown");
        window.reset();
    }

    void Application::update() {
        get_window().update();

    }

    int Application::run() {
        setup();

        _core_logger->info("Entering main loop");
        while (running) {
            // do stuff
            update();
        }

        _core_logger->info("Stopping main loop");

        shutdown();

        return 0;
    }

}