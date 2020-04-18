#pragma once


namespace engine::event {

    struct WindowEvent {

    };

    struct WindowResizeEvent {
        int width;
        int height;
    };

    struct WindowCloseEvent {};

}
