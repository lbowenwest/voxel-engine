#include "engine/window.h"

#include "platform/glwindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine {
    GLWindowImpl::GLWindowImpl(Window *owner) : WindowImpl{owner} {
        if (gl_window_count == 0) {
            glfwInit();
            glfwSetErrorCallback([](int error, const char *description) {
                spdlog::error("GLFW Error ({0}): {1}", error, description);
            });
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(
                static_cast<int>(owner->properties.size.x),
                static_cast<int>(owner->properties.size.y),
                owner->properties.title.c_str(),
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
        glfwSetWindowUserPointer(window, reinterpret_cast<Window *>(owner));

        if (!gladLoadGL()) {
            spdlog::error("Unable to load glad");
            glfwDestroyWindow(window);
            glfwTerminate();
            return;
        }

        glfwSetWindowSizeCallback(window, [](GLFWwindow *gl_window, int width, int height) {
            auto handler = reinterpret_cast<Window *>(glfwGetWindowUserPointer(gl_window));
            handler->properties.size = {width, height};
            handler->publish<event::WindowResizeEvent>(width, height);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow *gl_window) {
            auto handler = reinterpret_cast<Window *>(glfwGetWindowUserPointer(gl_window));
            handler->publish<event::WindowCloseEvent>();
        });

        glfwSetKeyCallback(window, [](GLFWwindow *gl_window, int key, int scancode, int action, int mods) {
            auto handler = reinterpret_cast<Window *>(glfwGetWindowUserPointer(gl_window));
            switch (action) {
                case GLFW_PRESS:
                    handler->publish<event::KeyPressedEvent>(key, 0, mods);
                    break;
                case GLFW_REPEAT:
                    handler->publish<event::KeyPressedEvent>(key, 1, mods);
                    break;
                case GLFW_RELEASE:
                    handler->publish<event::KeyReleasedEvent>(key);
                    break;
                default:
                    break;
            }
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow *gl_window, int button, int action, int mods) {
            auto handler = reinterpret_cast<Window *>(glfwGetWindowUserPointer(gl_window));
            switch (action) {
                case GLFW_PRESS:
                    handler->publish<event::MouseButtonPressedEvent>(button);
                    break;
                case GLFW_RELEASE:
                    handler->publish<event::MouseButtonReleasedEvent>(button);
                    break;
                default:
                    break;
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow *gl_window, double x_offset, double y_offset) {
            auto handler = reinterpret_cast<Window *>(glfwGetWindowUserPointer(gl_window));
            handler->publish<event::MouseScrolledEvent>(static_cast<float>(x_offset), static_cast<float>(y_offset));
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow *gl_window, double x_pos, double y_pos) {
            auto handler = reinterpret_cast<Window *>(glfwGetWindowUserPointer(gl_window));
            handler->publish<event::MouseMovedEvent>(static_cast<float>(x_pos), static_cast<float>(y_pos));
        });
    }

    GLWindowImpl::~GLWindowImpl() {
        glfwDestroyWindow(window);
        --gl_window_count;
        if (!gl_window_count) {
            glfwTerminate();
        }
    }

    void GLWindowImpl::update() {
        glClearColor(0.15f, 0.6f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void GLWindowImpl::maximise() {
        glfwMaximizeWindow(window);
    }

    void GLWindowImpl::minimise() {
        glfwIconifyWindow(window);
    }

    void GLWindowImpl::restore() {
        glfwRestoreWindow(window);
    }

    void GLWindowImpl::close() {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

}
