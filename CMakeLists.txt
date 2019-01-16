cmake_minimum_required(VERSION 3.12)
project(contaloc)

set(CMAKE_CXX_STANDARD 14)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(contaloc main.cpp)
target_link_libraries(contaloc ${CONAN_LIBS})