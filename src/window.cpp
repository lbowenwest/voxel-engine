#include "engine/window.h"

#include "platform/opengl/glwindow.h"

namespace engine {

    Window::Window(Properties properties) :
            properties{std::move(properties)},
            impl{WindowAPI::create(this)} {

    }

    WindowAPI::Platform  WindowAPI::platform = WindowAPI::Platform::OPENGL;

    template<typename EventDispatcher>
    std::unique_ptr<WindowAPI> WindowAPI::create(EventDispatcher* dispatcher) {
        switch (platform) {
            case Platform::NONE:
                spdlog::error("WindowPlatform::NONE not supported");
                return nullptr;

            case Platform::OPENGL:
                return std::make_unique<GLWindowImpl<EventDispatcher>>(dispatcher);

            default:
                spdlog::error("Unknown platform api");
                return nullptr;
        }
    }

}
