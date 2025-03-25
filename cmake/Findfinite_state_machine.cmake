set(finite_state_machine_FOUND TRUE)
set(finite_state_machine_ROOT_DIR ${CMAKE_SOURCE_DIR}/third/finite_state_machine)

find_path(finite_state_machine_INCLUDE_DIR NAMES finite_state_machine.hpp PATHS ${finite_state_machine_ROOT_DIR}/include)

set(finite_state_machine_INCLUDE_DIR ${finite_state_machine_INCLUDE_DIR})