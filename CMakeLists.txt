cmake_minimum_required(VERSION 3.10)
project(contaloc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Boost REQUIRED COMPONENTS system filesystem)
message(STATUS "Boost version: ${Boost_VERSION}")
message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")


add_executable(contaloc main.cpp)
target_link_libraries(contaloc PRIVATE Boost::system Boost::filesystem)