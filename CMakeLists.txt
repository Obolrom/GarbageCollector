cmake_minimum_required(VERSION 3.20)
project(GarbageCollector C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

# -----------------------
# VM library
# -----------------------
add_library(vm
        vm/src/virtual_machine.c
        vm/src/vm_object.c
        )
target_include_directories(vm PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

# -----------------------
# Main executable
# -----------------------
add_executable(GarbageCollector main.c)
target_link_libraries(GarbageCollector PRIVATE vm)

# -----------------------
# Tests (Unity)
# -----------------------
add_executable(vm_tests
        test/test_vm.c
        third_party/unity/unity.c
        )
target_include_directories(vm_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/unity
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
target_link_libraries(vm_tests PRIVATE vm)

enable_testing()
add_test(NAME vm_tests COMMAND vm_tests)
