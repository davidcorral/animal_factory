cmake_minimum_required(VERSION 3.0)

set( CMAKE_CXX_STANDARD 11 ) # C++11
find_package(PythonLibs 2.7 REQUIRED)

add_subdirectory(src)