#pragma once

#include <functional>
#include <string>
#include <utility>

#include <spdlog/spdlog.h>
#include <entt/entt.hpp>
#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>

#include "engine/events/keyboard.h"
#include "engine/events/mouse.h"
#include "engine/events/window.h"

namespace engine {

    enum class WindowMode {
        FULLSCREEN,
        WINDOWED
    };

    struct Properties {
        std::string title;
        glm::vec2 size;
//            WindowMode mode;
        Properties() = delete;
    };

    class Window;

    class WindowImpl {
    public:
        WindowImpl() = delete;
        explicit WindowImpl(Window *owner) : owner{owner} {}
        virtual ~WindowImpl() = default;

        virtual void update() = 0;
        virtual void maximise() = 0;
        virtual void minimise() = 0;
        virtual void restore() = 0;
        virtual void close() = 0;

    protected:
        Window *owner;
    };

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

    private:
        GLFWwindow *window;
    };

    class Window : private entt::emitter<Window> {

        friend class entt::emitter<Window>;

    public:
        using entt::emitter<Window>::on;
        using entt::emitter<Window>::once;
        using entt::emitter<Window>::clear;
        using entt::emitter<Window>::publish;

        Window() = delete;

        explicit Window(Properties properties) :
                properties{std::move(properties)},
                impl{std::make_unique<GLWindowImpl>(reinterpret_cast<Window *>(this))} {}

        ~Window() override = default;

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        void update() { impl->update(); }
        void maximise() { impl->maximise(); }
        void minimise() { impl->minimise(); }
        void restore() { impl->restore(); }
        void close() { impl->close(); }

        Properties properties;

    private:
        std::unique_ptr<WindowImpl> impl;

    };

}