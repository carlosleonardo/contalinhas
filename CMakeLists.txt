cmake_minimum_required(VERSION 3.10)
project(contaloc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Boost REQUIRED COMPONENTS system filesystem)


add_executable(contaloc main.cpp)
target_link_libraries(contaloc PRIVATE Boost::system Boost::filesystem)