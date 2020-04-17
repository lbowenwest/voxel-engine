#include "engine/window.h"

#include "platform/opengl/glwindow.h"

namespace engine {

    Window::Window(Properties properties) :
            properties{std::move(properties)},
            impl{WindowImpl::create(properties.platform, this)} {

    }

    template<typename EventDispatcher>
    std::unique_ptr<WindowImpl> WindowImpl::create(WindowPlatform platform, EventDispatcher* dispatcher) {
        switch (platform) {
            case WindowPlatform::NONE:
                spdlog::error("WindowPlatform::NONE not supported");
                return nullptr;

            case WindowPlatform::OPENGL:
                return std::make_unique<GLWindowImpl<EventDispatcher>>(dispatcher);

            default:
                spdlog::error("Unknown platform api");
                return nullptr;
        }
    }

}
