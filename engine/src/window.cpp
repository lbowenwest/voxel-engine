#include "engine/window.h"

#include "platform/glwindow.h"


namespace engine {

    Window::Window(Properties properties) :
            properties{std::move(properties)} {
        switch (properties.platform) {
            case WindowPlatform::OPENGL:
                impl = std::make_unique<GLWindowImpl<Window>>(reinterpret_cast<Window*>(this));
                break;
            default:
                break;
        }
    }

    void Window::update() {
        impl->update();
    }

    void Window::maximise() {
        impl->maximise();
    }

    void Window::minimise() {
        impl->minimise();
    }

    void Window::restore() {
        impl->restore();
    }

    void Window::close() {
        impl->close();
    }

    void* Window::get_native_window() {
        return impl->get_native();
    }


}
