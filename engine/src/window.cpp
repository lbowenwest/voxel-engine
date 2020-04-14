#include "engine/window.h"

#include "platform/glwindow.h"


namespace engine {

    Window::Window(Properties properties) :
            properties{std::move(properties)},
            impl{std::make_unique<GLWindowImpl>(reinterpret_cast<Window*>(this))} {}

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
