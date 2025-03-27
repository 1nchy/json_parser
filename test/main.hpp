#pragma once

#include <cstdio>
#include <cstdlib>
#include <cassert>

namespace {
void icy_assert(const char* _assertion, const char* _file, unsigned _line) {
    fprintf(stderr, "assert at %s, in %s:%u", _assertion, _file, _line);
    abort();
}
}

#define icy_assert(expr) \
    do { if (!static_cast<bool>(expr)) {\
    icy_assert(#expr, __FILE__, __LINE__); } } while (0)
