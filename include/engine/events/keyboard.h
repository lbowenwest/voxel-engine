#pragma once

namespace engine::event {

    struct KeyPressedEvent {
        int keycode;
        int repeat_count;
        int modifiers;
    };

    struct KeyReleasedEvent {
        int keycode;
        int modifiers;
    };

}