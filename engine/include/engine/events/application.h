#pragma once


namespace engine::event {
    struct QuitEvent {
        int return_code {};

        QuitEvent() : return_code{0};
        QuitEvent(int code) : return_code{code};
        ~QuitEvent() = default;
    };
}