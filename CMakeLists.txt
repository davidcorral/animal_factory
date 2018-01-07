cmake_minimum_required(VERSION 3.0)

set( CMAKE_CXX_STANDARD 11 ) # C++11
find_package(PythonLibs 2.7 REQUIRED)

add_subdirectory(src)

install( DIRECTORY ${CMAKE_SOURCE_DIR}/python/tests DESTINATION ${CMAKE_SOURCE_DIR}/dist/python/ )
install( DIRECTORY ${CMAKE_SOURCE_DIR}/python/animal_factory DESTINATION ${CMAKE_SOURCE_DIR}/dist/python/ )
install( FILES ${CMAKE_SOURCE_DIR}/python/test.py DESTINATION ${CMAKE_SOURCE_DIR}/dist/python/ )