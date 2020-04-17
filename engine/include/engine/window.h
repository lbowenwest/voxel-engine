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
        NONE = 0,
        OPENGL,
    };

    struct Properties {
        std::string title;
        glm::vec2 size;
        WindowPlatform platform{WindowPlatform::OPENGL};
        WindowMode mode{WindowMode::WINDOWED};

        Properties() = delete;
    };

    class WindowImpl {
    public:
        virtual ~WindowImpl() = default;

        template<typename EventDispatcher>
        static std::unique_ptr<WindowImpl> create(WindowPlatform platform, EventDispatcher* dispatcher);

        virtual void update() = 0;
        virtual void maximise() = 0;
        virtual void minimise() = 0;
        virtual void restore() = 0;
        virtual void close() = 0;
        virtual void* get_native() = 0;
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

        inline void update() { impl->update(); };
        inline void maximise() { impl->maximise(); }
        inline void minimise() { impl->minimise(); }
        inline void restore() { impl->restore(); }
        inline void close() { impl->close(); }
        inline void* get_native_window() { return impl->get_native(); }

        Properties properties;

    private:
        std::unique_ptr<WindowImpl> impl;

    };


}