#pragma once

namespace term {

void echo_off();
void echo_on();
void raw_on();
void raw_off();

struct EchoGuard {
    EchoGuard();
    ~EchoGuard();
    EchoGuard(const EchoGuard&)            = delete;
    EchoGuard& operator=(const EchoGuard&) = delete;
};

struct RawGuard {
    RawGuard();
    ~RawGuard();
    RawGuard(const RawGuard&)            = delete;
    RawGuard& operator=(const RawGuard&) = delete;
};

} 