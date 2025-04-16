#pragma once

struct InputModeComponent {
    enum class InputMode {
        DEFAULT,
        HARVEST,
        INVENTORY,
    };

    InputMode mode = InputMode::DEFAULT;
    InputMode last_mode = InputMode::DEFAULT;
};
