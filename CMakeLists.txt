cmake_minimum_required(VERSION 3.27)
project(elementary_cellular_automata)

set(CMAKE_CXX_STANDARD 17)

set(IMGUI_DIR src/imgui)
find_package(SDL2 REQUIRED)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ${SDL2_INCLUDE_DIRS})

add_executable(
        elementary_cellular_automata
        src/main.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp
        src/automaton.cpp
        src/automaton.h
)
target_link_libraries(elementary_cellular_automata SDL2::SDL2main SDL2::SDL2)
