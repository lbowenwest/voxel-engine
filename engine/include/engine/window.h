#pragma once

#include <functional>
#include <string>
#include <utility>

#include <spdlog/spdlog.h>
#include <entt/entt.hpp>
#include <glm/vec2.hpp>

#include "engine/events/keyboard.h"
#include "engine/events/mouse.h"
#include "engine/events/window.h"

namespace engine {

    enum class WindowMode {
        FULLSCREEN,
        WINDOWED
    };

    enum class WindowPlatform {
        OPENGL,
    };

    struct Properties {
        std::string title;
        glm::vec2 size;
        WindowPlatform platform{WindowPlatform::OPENGL};
        WindowMode mode{WindowMode::WINDOWED};

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
        virtual void* get_native() = 0;

    protected:
        Window *owner;
    };


    class Window : private entt::emitter<Window> {

        friend class entt::emitter<Window>;

    public:
        using entt::emitter<Window>::on;
        using entt::emitter<Window>::once;
        using entt::emitter<Window>::clear;
        using entt::emitter<Window>::publish;

        Window() = delete;
        explicit Window(Properties properties);
        ~Window() override = default;

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        inline void update();
        inline void maximise();
        inline void minimise();
        inline void restore();
        inline void close();
        inline void* get_native_window();

        Properties properties;

    private:
        std::unique_ptr<WindowImpl> impl;

    };

}