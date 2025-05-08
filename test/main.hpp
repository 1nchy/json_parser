#pragma once

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <string>

#include <concepts>
#include <functional>
#include <stdexcept>

#define __ICY_STR(x) #x
#define ICY_STR(x) __ICY_STR(x)

namespace {
void icy_abort(const char* _abortion, const char* _file, unsigned _line) {
    fprintf(stderr, "abort at %s, in %s:%u", _abortion, _file, _line);
    abort();
}
}

#define __EXPECT(expression, fail) \
    do { \
        if (!static_cast<bool>(expression)) { fail; } \
    } while (0)

#define __EXPECT_NOTHROW(statement, fail) \
    do { \
        bool caught_any_exception = false; \
        try { statement; } \
        catch (...) { caught_any_exception = true; } \
        if (caught_any_exception) { fail; } \
    } while (0)

#define __EXPECT_THROW(statement, expected_exception, fail) \
    do { \
        bool caught_expected_exception = false; \
        try { statement; } \
        catch (const expected_exception& e) \
        { caught_expected_exception = true; } \
        catch (...) {} \
        if (!caught_expected_exception) { fail; } \
    } while (0)

#define __EXPECT_THROW_MSG(statement, expected_exception, msg, fail) \
    do { \
        bool caught_expected_exception = false; \
        try { statement; } \
        catch (const expected_exception& e) \
        { caught_expected_exception = (std::string(e.what()) == msg); } \
        catch (...) {} \
        if (!caught_expected_exception) { fail; } \
    } while (0)

#define EXPECT(expression) \
    __EXPECT(expression, icy_abort(ICY_STR(expression), __FILE__, __LINE__))
#define EXPECT_TRUE(expression) EXPECT(expression)
#define EXPECT_FALSE(expression) \
    __EXPECT(!expression, icy_abort(ICY_STRCAT(!, expression), __FILE__, __LINE__))
#define EXPECT_EQ(x, y) \
    __EXPECT(((x) == (y)), icy_abort(ICY_STR(x == y), __FILE__, __LINE__))
#define EXPECT_NQ(x, y) \
    __EXPECT(((x) != (y)), icy_abort(ICY_STR(x != y), __FILE__, __LINE__))
#define EXPECT_LT(x, y) \
    __EXPECT(((x) < (y)), icy_abort(ICY_STR(x < y), __FILE__, __LINE__))
#define EXPECT_GT(x, y) \
    __EXPECT(((x) > (y)), icy_abort(ICY_STR(x > y), __FILE__, __LINE__))
#define EXPECT_LE(x, y) \
    __EXPECT(((x) <= (y)), icy_abort(ICY_STR(x <= y), __FILE__, __LINE__))
#define EXPECT_GE(x, y) \
    __EXPECT(((x) >= (y)), icy_abort(ICY_STR(x >= y), __FILE__, __LINE__))

#define EXPECT_NOTHROW(statement) \
    __EXPECT_NOTHROW(statement, icy_abort(ICY_STR(statement), __FILE__, __LINE__))

#define EXPECT_THROW(ex, statement) \
    __EXPECT_THROW(statement, ex, icy_abort(ICY_STR(statement), __FILE__, __LINE__))

#define EXPECT_THROW_MSG(ex, statement, msg) \
    __EXPECT_THROW_MSG(statement, ex, msg, icy_abort(ICY_STR(statement), __FILE__, __LINE__))
