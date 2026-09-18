#pragma once
#include <string>

namespace esc {
//     ##__CURSOR__##
    constexpr const char* CLEAR_SCREEN = "\x1b[2J";
    constexpr const char* CURSOR_HOME  = "\x1b[H";
    constexpr const char* CURSOR_HIDE  = "\x1b[?25l";
    constexpr const char* CURSOR_SHOW  = "\x1b[?25h";

//     ##__STYLE__##
    constexpr const char* RESET = "\x1b[0m";

//     ##__MOUSE__##
    constexpr const char* MOUSE_ON  = "\x1b[?1000h\x1b[?1006h";
    constexpr const char* MOUSE_OFF = "\x1b[?1000l\x1b[?1006l";

//     ##__PASTE__##
    constexpr const char* PASTE_ON  = "\x1b[?2004h";
    constexpr const char* PASTE_OFF = "\x1b[?2004l";

//     ##__ALT_SCREEN__##
    constexpr const char* ALT_SCREEN_ON  = "\x1b[?1049h";
    constexpr const char* ALT_SCREEN_OFF = "\x1b[?1049l";

//     ##__QUERY__##
    constexpr const char* CURSOR_POS_QUERY = "\x1b[6n";

//     ##__HELPERS__##
    inline std::string move_to(int row, int col) {
        return "\x1b[" + std::to_string(row) + ";" + std::to_string(col) + "H";
    }
    inline std::string fg_rgb(int r, int g, int b) {
        return "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }
    inline std::string bg_rgb(int r, int g, int b) {
        return "\x1b[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }
}