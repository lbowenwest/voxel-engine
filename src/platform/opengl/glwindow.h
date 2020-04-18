#pragma once

#include "engine/window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine {
    static uint8_t gl_window_count = 0;

    template<typename EventDispatcher>
    class GLWindowImpl : public WindowAPI {
    public:
        GLWindowImpl() = delete;
        explicit GLWindowImpl(EventDispatcher *dispatcher);
        ~GLWindowImpl() override;

        void update() override;
        void maximise() override;
        void minimise() override;
        void restore() override;
        void close() override;
        void* get_native() override;

    private:
        EventDispatcher *dispatcher;
        GLFWwindow *window;
    };

    template<typename EventDispatcher>
    GLWindowImpl<EventDispatcher>::GLWindowImpl(EventDispatcher *dispatcher) : dispatcher{dispatcher} {
        if (gl_window_count == 0) {
            glfwInit();
            glfwSetErrorCallback([](int error, const char *description) {
                spdlog::error("GLFW Error ({0}): {1}", error, description);
            });
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(
                static_cast<int>(dispatcher->properties.size.x),
                static_cast<int>(dispatcher->properties.size.y),
                dispatcher->properties.title.c_str(),
                nullptr,
                nullptr
        );
        if (!window) {
            spdlog::error("Failed to create GLFW window");
            glfwTerminate();
            return;
        }
        ++gl_window_count;

        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, reinterpret_cast<EventDispatcher*>(dispatcher));

        if (!gladLoadGL()) {
            spdlog::error("Unable to load glad");
            glfwDestroyWindow(window);
            glfwTerminate();
            return;
        }

        glfwSetWindowSizeCallback(window, [](GLFWwindow *gl_window, int width, int height) {
            auto handler = reinterpret_cast<EventDispatcher*>(glfwGetWindowUserPointer(gl_window));
            handler->properties.size = {width, height};
            handler->template publish<event::WindowResizeEvent>(width, height);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow *gl_window) {
            auto handler = reinterpret_cast<EventDispatcher*>(glfwGetWindowUserPointer(gl_window));
            handler->template publish<event::WindowCloseEvent>();
        });

        glfwSetKeyCallback(window, [](GLFWwindow *gl_window, int key, int scancode, int action, int mods) {
            auto handler = reinterpret_cast<EventDispatcher*>(glfwGetWindowUserPointer(gl_window));
            switch (action) {
                case GLFW_PRESS:
                    handler->template publish<event::KeyPressedEvent>(key, 0, mods);
                    break;
                case GLFW_REPEAT:
                    handler->template publish<event::KeyPressedEvent>(key, 1, mods);
                    break;
                case GLFW_RELEASE:
                    handler->template publish<event::KeyReleasedEvent>(key);
                    break;
                default:
                    break;
            }
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow *gl_window, int button, int action, int mods) {
            auto handler = reinterpret_cast<EventDispatcher*>(glfwGetWindowUserPointer(gl_window));
            switch (action) {
                case GLFW_PRESS:
                    handler->template publish<event::MouseButtonPressedEvent>(button);
                    break;
                case GLFW_RELEASE:
                    handler->template publish<event::MouseButtonReleasedEvent>(button);
                    break;
                default:
                    break;
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow *gl_window, double x_offset, double y_offset) {
            auto handler = reinterpret_cast<EventDispatcher*>(glfwGetWindowUserPointer(gl_window));
            handler->template publish<event::MouseScrolledEvent>(static_cast<float>(x_offset), static_cast<float>(y_offset));
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow *gl_window, double x_pos, double y_pos) {
            auto handler = reinterpret_cast<Window *>(glfwGetWindowUserPointer(gl_window));
            handler->publish<event::MouseMovedEvent>(static_cast<float>(x_pos), static_cast<float>(y_pos));
        });
    }

    template<typename EventDispatcher>
    GLWindowImpl<EventDispatcher>::~GLWindowImpl() {
        glfwDestroyWindow(window);
        --gl_window_count;
        if (!gl_window_count) {
            glfwTerminate();
        }
    }

    template<typename EventDispatcher>
    void GLWindowImpl<EventDispatcher>::update() {
        glClearColor(0.15f, 0.6f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    template<typename EventDispatcher>
    void GLWindowImpl<EventDispatcher>::maximise() {
        glfwMaximizeWindow(window);
    }

    template<typename EventDispatcher>
    void GLWindowImpl<EventDispatcher>::minimise() {
        glfwIconifyWindow(window);
    }

    template<typename EventDispatcher>
    void GLWindowImpl<EventDispatcher>::restore() {
        glfwRestoreWindow(window);
    }

    template<typename EventDispatcher>
    void GLWindowImpl<EventDispatcher>::close() {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    template<typename EventDispatcher>
    void* GLWindowImpl<EventDispatcher>::get_native() {
        return window;
    }

}