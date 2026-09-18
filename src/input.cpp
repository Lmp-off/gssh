#include <gssh/input.hpp>
#include <gssh/c_esc.hpp>

#include <unistd.h>
#include <iostream>
#include <string>
#include <charconv>
#include <cctype>
#include <array>

namespace input {

namespace {

int read_byte() {
    char c;
    ssize_t n = ::read(STDIN_FILENO, &c, 1);
    return (n == 1) ? static_cast<unsigned char>(c) : -1;
}

std::optional<std::array<int, 3>> parse_three(std::string_view s) {
    std::array<int, 3> out{};
    size_t start = 0;

    for (int i = 0; i < 3; ++i) {
        size_t semi = s.find(';', start);
        std::string_view part = (i < 2)
            ? s.substr(start, semi - start)
            : s.substr(start);

        if (part.empty()) return std::nullopt;

        int value = 0;
        auto [ptr, ec] = std::from_chars(part.data(),
                                         part.data() + part.size(),
                                         value);
        if (ec != std::errc{} || ptr != part.data() + part.size())
            return std::nullopt;

        out[i] = value;

        if (i < 2) {
            if (semi == std::string_view::npos) return std::nullopt;
            start = semi + 1;
        }
    }
    return out;
}}

void mouse_on()  { std::cout << esc::MOUSE_ON  << std::flush; }
void mouse_off() { std::cout << esc::MOUSE_OFF << std::flush; }

std::optional<MouseEvent> read_mouse() {
    if (read_byte() != '\033') return std::nullopt;
    if (read_byte() != '[')    return std::nullopt;
    if (read_byte() != '<')    return std::nullopt;

    std::string body;
    body.reserve(16);

    for (;;) {
        int c = read_byte();
        if (c < 0) return std::nullopt;

        if (c == 'M' || c == 'm') {
            auto nums = parse_three(body);
            if (!nums) return std::nullopt;

            MouseEvent ev;
            ev.button  = (*nums)[0];
            ev.x       = (*nums)[1];
            ev.y       = (*nums)[2];
            ev.pressed = (c == 'M');
            return ev;
        }

        if (!std::isdigit(c) && c != ';') return std::nullopt;
        body.push_back(static_cast<char>(c));

        if (body.size() > 32) return std::nullopt;  // защита от мусора
    }
}}