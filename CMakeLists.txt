cmake_minimum_required(VERSION 3.16)
project(RtsGameTutorial)

# find_package(raylib 5.5 REQUIRED)
# find_package(GLFW REQUIRED)
# find_package(pthread REQUIRED)
include_directories("/usr/local/include/raylib")

include_directories(inc)
add_subdirectory(src)

# add_library(game "")
# add_library(raylib)

add_executable(rts src/main.cpp)
target_link_libraries(rts
                                    dl
                                    pthread
                                    "/usr/local/lib/raylib/libraylib.a")
                                    # raylib)