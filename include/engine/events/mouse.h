#pragma once

namespace engine::event {
    struct MouseMovedEvent {
        float x;
        float y;
    };

    struct MouseScrolledEvent {
        float x_offset;
        float y_offset;
    };

    struct MouseButtonPressedEvent {
        int button;
    };

    struct MouseButtonReleasedEvent {
        int button;
    };
}