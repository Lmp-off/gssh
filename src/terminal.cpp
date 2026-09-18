#include <gssh/terminal.hpp>

#include <termios.h>
#include <unistd.h>

namespace term {

namespace {

termios g_orig{};
bool    g_orig_saved = false;

bool& echo_saved() { static bool b = false; return b; }
bool& raw_saved()  { static bool b = false; return b; }

bool ensure_orig_saved() {
    if (g_orig_saved) return true;
    if (!isatty(STDIN_FILENO)) return false;
    if (tcgetattr(STDIN_FILENO, &g_orig) != 0) return false;
    g_orig_saved = true;
    return true;
}}

void echo_off() {
    if (echo_saved()) return;
    if (!ensure_orig_saved()) return;

    termios t = g_orig;
    t.c_lflag &= ~ECHO;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == 0)
        echo_saved() = true;
}

void echo_on() {
    if (!echo_saved()) return;
    tcsetattr(STDIN_FILENO, TCSANOW, &g_orig);
    echo_saved() = false;
}

void raw_on() {
    if (raw_saved()) return;
    if (!ensure_orig_saved()) return;

    termios t = g_orig;
    t.c_lflag &= ~(ICANON | ECHO | ISIG);
    t.c_cc[VMIN]  = 1;
    t.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == 0) {
        raw_saved()  = true;
        echo_saved() = true;
    }
}

void raw_off() {
    if (!raw_saved()) return;
    tcsetattr(STDIN_FILENO, TCSANOW, &g_orig);
    raw_saved()  = false;
    echo_saved() = false;
}

EchoGuard::EchoGuard()  { echo_off(); }
EchoGuard::~EchoGuard() { echo_on();  }

RawGuard::RawGuard()  { raw_on();  }
RawGuard::~RawGuard() { raw_off(); }}