cmake_minimum_required(VERSION 3.8)

project("game")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SDL_STATIC ON CACHE BOOL "USE STATIC SDL" FORCE)
set(SDL_SHARED OFF CACHE BOOL "USE SHARED SDL" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "BUILD SHARED LIBS" FORCE)

# Include c++ files
file(GLOB_RECURSE CXX_SOURCE "src/*.cpp")
file(GLOB IMGUI_SOURCE 
    "deps/imgui-docking/imgui.cpp"
    "deps/imgui-docking/imgui_widgets.cpp"
    "deps/imgui-docking/imgui_tables.cpp"
    "deps/imgui-docking/imgui_draw.cpp"
    "deps/imgui-docking/imgui_demo.cpp"
    "deps/imgui-docking/backends/imgui_impl_sdlrenderer.cpp"
    "deps/imgui-docking/backends/imgui_impl_opengl3.cpp"
    "deps/imgui-docking/backends/imgui_impl_sdl.cpp"
)

add_executable(${PROJECT_NAME} ${CXX_SOURCE} ${IMGUI_SOURCE})

target_precompile_headers(${PROJECT_NAME} PRIVATE "src/pch.h")
target_include_directories(${PROJECT_NAME} PRIVATE
    "src"
    "deps/imgui-docking"
    "deps/glm"
    "deps/sdl/include"
    "deps/sdl_image"
    "deps/entt/src"
    "deps/spdlog/include"
)

add_subdirectory(deps/SDL)
add_subdirectory(deps/SDL_image)

target_link_libraries(${PROJECT_NAME} "SDL2-static" "SDL2_image")

add_custom_command(
    TARGET "game" PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/res"
    "${CMAKE_BINARY_DIR}/res"
)