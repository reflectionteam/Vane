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
    src/ui/mainwindow/header/header.c
    src/ui/mainwindow/sidebar/sidebar.c
    src/ui/mainwindow/overview/overview.c
    src/ui/mainwindow/mods/mods.c
    src/ui/mainwindow/servers/servers.c
    src/ui/mainwindow/screenshots/screenshots.c
    src/ui/mainwindow/logs/logs.c
    src/ui/renderer/clay_sdl3.c
    src/ui/styles/button/button_style.c
    src/ui/widgets/button/button.c
    src/ui/widgets/icon/icons.c
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
