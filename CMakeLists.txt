cmake_minimum_required(VERSION 3.28)
project(PongPong)

set(CMAKE_CXX_STANDARD 17)

# Add executable target
add_executable(PongPong main.cpp)

# Set path to raylib and glfw library directories
set(raylib_DIR "C:/raylib/w64devkit/x86_64-w64-mingw32")
set(glfw_LIB_DIR "C:/raylib/raylib/examples/others/external/lib")

# Find raylib package
find_package(raylib 3.7 QUIET)

# If raylib is not found, fetch and build it
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/3.7.0.tar.gz
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Link raylib library
target_link_libraries(PongPong PRIVATE raylib)

# Link glfw library
target_link_directories(PongPong PRIVATE ${glfw_LIB_DIR})
target_link_libraries(PongPong PRIVATE glfw)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(PongPong PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(PongPong PRIVATE "-framework IOKit")
    target_link_libraries(PongPong PRIVATE "-framework Cocoa")
    target_link_libraries(PongPong PRIVATE "-framework OpenGL")
endif()
