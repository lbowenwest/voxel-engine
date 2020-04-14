#pragma once

#include "engine/window.h"

struct GLFWwindow;

namespace engine {
    static uint8_t gl_window_count = 0;

    class GLWindowImpl : public WindowImpl {
    public:
        GLWindowImpl() = delete;
        explicit GLWindowImpl(Window *owner);
        ~GLWindowImpl() override;

        void update() override;
        void maximise() override;
        void minimise() override;
        void restore() override;
        void close() override;
        void* get_native() override;

    private:
        GLFWwindow *window;
    };
}