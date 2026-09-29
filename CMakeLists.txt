cmake_minimum_required(VERSION 3.20)
project(Vane C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

add_library(clay STATIC
    src/vendor/clay_impl.c
)
target_include_directories(clay PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/clay
)

add_executable(vane
    src/main.c
    src/core/app_state.c
    src/ui/mainwindow/mainwindow.c
    src/ui/views/sidebar.c
    src/ui/views/content_view.c
    src/ui/renderer/clay_sdl3.c
    src/ui/styles/button/button_style.c
    src/ui/widgets/button/button.c
)

target_include_directories(vane PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(vane PRIVATE 
    clay 
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
