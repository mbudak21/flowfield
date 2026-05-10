cmake_minimum_required(VERSION 4.3)
project(flowfield C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)                                                                                                                                                                                      
    set(CMAKE_BUILD_TYPE Release)                                                                                                                                                                             
endif()

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE) # enable wayland on linux
set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE) # disable x11 on linux (switch these settings around as you please)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "6.0"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

# 2. Fetch raygui
FetchContent_Declare(
  raygui
  GIT_REPOSITORY https://github.com/raysan5/raygui
  GIT_TAG "4.0"
)
FetchContent_MakeAvailable(raygui)




add_executable(${PROJECT_NAME} src/main.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${raygui_SOURCE_DIR}/src)
add_subdirectory(lib)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib open-simplex-noise)
