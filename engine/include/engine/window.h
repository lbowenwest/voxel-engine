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


    class Window : private entt::emitter<Window> {

        friend class entt::emitter<Window>;

    public:
        using entt::emitter<Window>::on;
        using entt::emitter<Window>::once;
        using entt::emitter<Window>::clear;
        using entt::emitter<Window>::publish;

        struct Properties {
            std::string title;
            glm::vec2 size;

            Properties() : title{"Window"}, size{1280, 720} {}

            Properties(std::string title, glm::vec2 size) :
                    title{std::move(title)}, size{size} {}
        };

        Window() : properties{} {}

        Window(std::string title, glm::vec2 size) : properties{std::move(title), size} {}


        virtual void update() {}

        Properties properties;

    };


    static uint8_t gl_window_count = 0;

    class GLWindow : private entt::emitter<GLWindow>, public Window {

        friend class entt::emitter<GLWindow>;

    public:
        using entt::emitter<GLWindow>::on;
        using entt::emitter<GLWindow>::once;
        using entt::emitter<GLWindow>::clear;
        using entt::emitter<GLWindow>::publish;

        GLWindow() : Window{}, entt::emitter<GLWindow>{} {
            if (gl_window_count == 0) {
                glfwInit();
                glfwSetErrorCallback([](int error, const char *description) {
                    spdlog::error("GLFW Error ({0}): {1}", error, description);
                });
            }
            window = glfwCreateWindow(
                    static_cast<int>(properties.size.x),
                    static_cast<int>(properties.size.y),
                    properties.title.c_str(),
                    nullptr,
                    nullptr
            );
            ++gl_window_count;

            glfwMakeContextCurrent(window);
            glfwSetWindowUserPointer(window, reinterpret_cast<GLWindow *>(this));

            glfwSetWindowSizeCallback(window, [](GLFWwindow *gl_window, int width, int height) {
                auto handler = reinterpret_cast<GLWindow *>(glfwGetWindowUserPointer(gl_window));
                handler->properties.size = {width, height};
                handler->publish<event::WindowResizeEvent>(width, height);
            });

            glfwSetWindowCloseCallback(window, [](GLFWwindow *gl_window) {
                auto handler = reinterpret_cast<GLWindow *>(glfwGetWindowUserPointer(gl_window));
                handler->publish<event::WindowCloseEvent>();
            });

            glfwSetKeyCallback(window, [](GLFWwindow *gl_window, int key, int scancode, int action, int mods) {
                auto handler = reinterpret_cast<GLWindow *>(glfwGetWindowUserPointer(gl_window));
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
                auto handler = reinterpret_cast<GLWindow *>(glfwGetWindowUserPointer(gl_window));
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
                auto handler = reinterpret_cast<GLWindow *>(glfwGetWindowUserPointer(gl_window));
                handler->publish<event::MouseScrolledEvent>(static_cast<float>(x_offset), static_cast<float>(y_offset));
            });

            glfwSetCursorPosCallback(window, [](GLFWwindow *gl_window, double x_pos, double y_pos) {
                auto handler = reinterpret_cast<GLWindow *>(glfwGetWindowUserPointer(gl_window));
                handler->publish<event::MouseMovedEvent>(static_cast<float>(x_pos), static_cast<float>(y_pos));
            });
        }

        ~GLWindow() override {
            glfwDestroyWindow(window);
            --gl_window_count;
            if (!gl_window_count) {
                glfwTerminate();
            }
        }

        void update() override {
            glfwPollEvents();
            glfwSwapBuffers(window);
        }


    private:
        GLFWwindow *window;

    };

}