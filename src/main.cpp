#ifdef WIN32
#endif

#ifdef ARCH
#endif

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

#include <thread>
#include <chrono>

#include <termios.h>
#include <unistd.h>

#include <gssh/terminal.hpp>
#include <gssh/c_esc.hpp>
#include <gssh/input.hpp>

void test() {
    std::cout << esc::ALT_SCREEN_ON;
    std::cout << esc::CURSOR_HIDE;
    std::cout << esc::CLEAR_SCREEN;
    std::cout << esc::CURSOR_HOME;
    std::cout << esc::move_to(5, 10);
    std::cout << "Hello ";
    std::cout << esc::fg_rgb(255, 0, 0);
    std::cout << "Red text";
    std::cout << esc::RESET;
    std::cout << std::flush;

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << esc::CURSOR_SHOW;
    std::cout << esc::ALT_SCREEN_OFF;
    std::cout << std::flush;
}

int main() {
    term::RawGuard raw;
    input::mouse_on();

    while (true) {
        if (auto ev = input::read_mouse()) {
            std::cout << "Mouse: x=" << ev->x
                      << " y=" << ev->y
                      << " btn=" << ev->button
                      << (ev->pressed ? " press" : " release")
                      << "\n" << std::flush;
        }
    }

    input::mouse_off();
    return 0;
}