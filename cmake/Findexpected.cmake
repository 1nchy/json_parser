set(expected_FOUND TRUE)
set(expected_ROOT_DIR ${CMAKE_SOURCE_DIR}/third/expected)

find_path(expected_INCLUDE_DIR NAMES tl/expected.hpp PATHS ${expected_ROOT_DIR}/include)

set(expected_INCLUDE_DIR ${expected_INCLUDE_DIR})