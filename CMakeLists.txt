cmake_minimum_required(VERSION 3.16)

project("glBox" LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL3
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)

set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL_UNINSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory("vendor/sdl" EXCLUDE_FROM_ALL)
add_subdirectory("vendor/glm")
add_subdirectory("vendor/glad")
add_subdirectory("vendor/stb")

file(GLOB_RECURSE "SOURCES" CONFIGURE_DEPENDS "src/*.cpp")
add_executable("glBox" "${SOURCES}")

# Enable ALL warnings
if(MSVC)
  target_compile_options("glBox" PRIVATE /W4)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options("glBox" PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options("glBox" PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_include_directories("glBox" PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries("glBox" PRIVATE SDL3::SDL3-static glm glad stb)