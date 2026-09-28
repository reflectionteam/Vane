cmake_minimum_required(VERSION 3.20)
project(Vane C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(clay STATIC
    src/vendor/clay_impl.c
)

target_include_directories(clay PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/clay
)

add_executable(vane
    src/main.c
)

target_link_libraries(vane PRIVATE clay)
