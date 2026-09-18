#pragma once
#include <cstdint>
#include <optional>

namespace input {

struct MouseEvent {
    int  x = 0;
    int  y = 0;
    int  button = 0;   // 0=левая, 1=средняя, 2=правая, 64/65=колесо
    bool pressed = false;
    bool valid = false;
};

void mouse_on();
void mouse_off();

std::optional<MouseEvent> read_mouse();

}