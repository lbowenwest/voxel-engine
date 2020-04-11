#pragma once

namespace engine {
    class Application {

    public:
        Application();
        virtual ~Application();

        virtual void run();
    };


    extern Application* create_application();

}
