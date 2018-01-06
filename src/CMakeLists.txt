set( LIB_NAME animal_factory )

file(GLOB SOURCE_FILES "*.h" "*.cpp" )

add_library( ${LIB_NAME} SHARED ${SOURCE_FILES} )

include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(${LIB_NAME} ${PYTHON_LIBRARY} )

# Set Suffix
set(LIB_SUFFIX ".so")
if (WIN32)
    set(LIB_SUFFIX ".pyd")
endif()

set_target_properties(${LIB_NAME}
        PROPERTIES PREFIX "" 
        SUFFIX ${LIB_SUFFIX})

install( TARGETS ${LIB_NAME} 
         LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/dist/ )

install( FILES ${CMAKE_SOURCE_DIR}/src/test.py DESTINATION ${CMAKE_SOURCE_DIR}/dist/ )

        