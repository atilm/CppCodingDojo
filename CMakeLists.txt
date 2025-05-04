cmake_minimum_required(VERSION 3.28)
project(CodingDojo VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Catch2 3 REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(Tests ${SOURCES})
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)