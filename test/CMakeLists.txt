include_directories(
    ${BANDIT_INCLUDE_DIR}
)

add_subdirectory(geometry)
add_subdirectory(worldtree)
add_subdirectory(property)


set(TEST_TARGET test_all)
file(GLOB_RECURSE TEST_FILES
    "*.cpp"
)

add_definitions(-DTEST_ALL)

source_group("Tests" FILES ${TEST_FILES})

add_executable(${TEST_TARGET}
	${TEST_FILES}
	${SRC_FILES_EXCEPT_MAIN}
)

target_link_libraries(${TEST_TARGET}
	${LIBS_TO_LINK}
)

set_target_properties(${TEST_TARGET}
    PROPERTIES
    LINKER_LANGUAGE CXX
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
)